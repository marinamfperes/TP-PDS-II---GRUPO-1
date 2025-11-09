#include "GerenciadorTarefas.h"

#include "Quadro.h"
#include "Notificador.h"
#include "Relogio.h"
#include "Tarefa.h"

#include <algorithm>
#include <stdexcept>
#include <ctime>

//construtor
//recebe ponteiros para Notificador e Relogio (podem ser nullptr)
GerenciadorTarefas::GerenciadorTarefas(Notificador* notificador, Relogio* relogio)
    : quadro_(nullptr), notificador_(notificador), relogio_(relogio) {}

//conecta o Quadro ao gerenciador
void GerenciadorTarefas::setQuadro(Quadro* q) {
    this->quadro_ = q;
}

//cria tarefa
void GerenciadorTarefas::criarTarefa(Tarefa tarefa) {
    const std::time_t agora = relogio_ ? relogio_->agora() : std::time(nullptr);

    std::string erro;
    if (!tarefa.validar(agora, &erro)) {
        throw std::invalid_argument("Falha ao criar tarefa: " + erro);
    }

    //garante status inicial "A Fazer"
    tarefa.atualizarStatus("A Fazer");

    //armazena no vetor interno
    tarefas_.push_back(tarefa);

    //reflete no Quadro (insere na coluna correspondente)
    if (quadro_) {
        std::string st = tarefa.getStatus(); // lvalue para compatibilidade com ambos os protótipos
        quadro_->moverTarefaParaColuna(tarefa.getId(), st);
    }
}

//edita tarefa
void GerenciadorTarefas::editarTarefa(int id, Tarefa tarefaAtualizada) {
    const std::time_t agora = relogio_ ? relogio_->agora() : std::time(nullptr);

    std::string erro;
    if (!tarefaAtualizada.validar(agora, &erro)) {
        throw std::invalid_argument("Falha ao editar tarefa: " + erro);
    }

    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) {
        throw std::runtime_error("Tarefa não encontrada para edição.");
    }

    
    //se o chamador não explicitou um status novo, mantém o atual
    std::string statusDesejado = tarefaAtualizada.getStatus().empty()
                                 ? it->getStatus()
                                 : tarefaAtualizada.getStatus();

    //copia campos (o id permanece o mesmo)
    it->setTitulo(tarefaAtualizada.getTitulo());
    it->setDescricao(tarefaAtualizada.getDescricao());
    it->setAgendada(tarefaAtualizada.getAgendada());
    it->setVencimento(tarefaAtualizada.getVencimento());
    it->setPrioridade(tarefaAtualizada.getPrioridade());

    it->clearTags();
    for (const auto& tag : tarefaAtualizada.getTags()) {
        it->addTag(tag);
    }

    it->atualizarStatus(statusDesejado);

    if (quadro_) {
        std::string st = statusDesejado;
        quadro_->moverTarefaParaColuna(it->getId(), st);
    }
}

//exclui tarefa
void GerenciadorTarefas::excluirTarefa(int id) {
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return;

    //usa status da tarefa para remover do quadro antes de apagar do vetor interno
    if (quadro_) {
        quadro_->removerTarefaPorId(id);
    }
    tarefas_.erase(it);
}

//mover tarefa (atualiza status no vetor interno e reflete no Quadro)
void GerenciadorTarefas::moverTarefa(int id, const std::string& novoStatus) {
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return;

    it->atualizarStatus(novoStatus);

    if (quadro_) {
        std::string st = novoStatus; // lvalue compatível com ambas as assinaturas do Quadro
        quadro_->moverTarefaParaColuna(id, st);
    }
}

//listar tarefas por status
std::vector<Tarefa> GerenciadorTarefas::listarTarefasPorStatus(const std::string& status) const {
    std::vector<Tarefa> out;
    out.reserve(tarefas_.size());
    for (const auto& t : tarefas_) {
        if (t.getStatus() == status) out.push_back(t);
    }
    return out;
}

//acionar rotina de notificação
void GerenciadorTarefas::notificarTarefas() {
    if (!notificador_) return;
}

//contagem de pendências
int GerenciadorTarefas::contarTarefasPendentes() const {
    int total = 0;
    for (const auto& t : tarefas_) {
        if (t.getStatus() == "A Fazer" || t.getStatus() == "Fazendo") {
            ++total;
        }
    }
    return total;
}