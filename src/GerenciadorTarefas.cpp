#include "GerenciadorTarefas.h"

#include <algorithm>
#include <stdexcept>
#include <ctime>

//construtor
//recebe ponteiros para Notificador e Relogio (podem ser nullptr)
GerenciadorTarefas::GerenciadorTarefas(Relogio* relogio) 
: relogio_(relogio) {}

//cria tarefa
void GerenciadorTarefas::criarTarefa(Tarefa tarefa) {

    //armazena no vetor interno
    tarefas_.push_back(tarefa);

}

//edita tarefa
void GerenciadorTarefas::editarTarefa(int id, Tarefa tarefaAtualizada) {
    const std::time_t agora = relogio_ ? relogio_->agora() : std::time(nullptr);

    std::string erro;
    if (!tarefaAtualizada.validar(agora, &erro)) {
        throw std::invalid_argument("Falha ao editar tarefa: " + erro);
    }

    //procura pela tarefa com o id fornecido
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) {
        throw std::runtime_error("Tarefa não encontrada para edição.");
    }

    //copia campos (o id permanece o mesmo)
    it->setTitulo(tarefaAtualizada.getTitulo());
    it->setDescricao(tarefaAtualizada.getDescricao());
    it->setAgendada(tarefaAtualizada.getAgendada());
    it->setVencimento(tarefaAtualizada.getVencimento());
    it->setPrioridade(tarefaAtualizada.getPrioridade());

    for (const auto& tag : tarefaAtualizada.getTags()) {
        it->addTag(tag);  //adiciona cada nova tag sem limpar as antigas
    }
    it->atualizarStatus(tarefaAtualizada.getStatus());

}

//exclui tarefa
void GerenciadorTarefas::excluirTarefa(int id) {
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return;

    tarefas_.erase(it);
}

//mover tarefa (atualiza status no vetor interno)
void GerenciadorTarefas::moverTarefa(int id, const std::string& novoStatus) {
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return;

    it->atualizarStatus(novoStatus);

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

//procurar e retornar uma tarefa específica pelo seu id
bool GerenciadorTarefas::obterTarefaPorId(int id, Tarefa& out) const {
    auto it = std::find_if(tarefas_.begin(), tarefas_.end(),
                           [id](const Tarefa& t){ return t.getId() == id; });
    if (it == tarefas_.end()) return false;
    out = *it; //copia tarefa encontrada para objeto de saísa
    return true;
}

const std::vector<Tarefa>& GerenciadorTarefas::getTodasTarefas() const {
    return tarefas_;  //retorna referência para vetor de tarefas
}