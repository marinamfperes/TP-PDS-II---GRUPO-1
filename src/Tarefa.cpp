#include "Tarefa.h"
#include <stdexcept>   //para lançar exceções em validações
#include <algorithm>   //para algoritmos de busca/remoção -> std::find
#include <utility>     //para utilitários -> std::move

//gerador simples de IDs únicos
//"static" garante um contador único para todas as Tarefas
//ada nova Tarefa recebe id = GERADOR_ID_TAREFA++
static int GERADOR_ID_TAREFA = 1;

//construtor que inicializ todos os campos
Tarefa::Tarefa(std::string titulo_,
               std::string descricao_,
               std::string categoria_,
               std::time_t agendada_,
               std::time_t vencimento_,
               int prioridade_)
    : id(GERADOR_ID_TAREFA++), //gera id único e incrementa o contator
      titulo(std::move(titulo_)),
      descricao(std::move(descricao_)),
      categoria(std::move(categoria_)),
      agendada(agendada_),
      vencimento(vencimento_),
      prioridade(prioridade_),
      status("A Fazer") //status inicial padrão do quadro Kanban
{
    //valida o título, que não pode ser vazio
    if (!validarCampos()) {
        //mensagem que destaca o argumento inválido
        throw std::invalid_argument("Título da tarefa não pode ser vazio.");
    }

    //valida as datas agendada e de vencimento
    if (!validarDatas(std::time(nullptr))) {
        throw std::invalid_argument("Datas inválidas para a tarefa.");
    }
}

//getters (acessam dados internos sem permitir modificação)
int Tarefa::getId() const               { return id; }
std::string Tarefa::getTitulo() const   { return titulo; }
std::string Tarefa::getDescricao() const{ return descricao; }
std::string Tarefa::getCategoria() const{ return categoria; }
std::time_t Tarefa::getAgendada() const { return agendada; }
std::time_t Tarefa::getVencimento() const { return vencimento; }
int Tarefa::getPrioridade() const       { return prioridade; }
std::string Tarefa::getStatus() const   { return status; }

//troca o status textual da tarefa no Kanban
// aceita só "A Fazer", "Fazendo" ou "Feito"
void Tarefa::atualizarStatus(std::string novoStatus) {
    if (novoStatus == "A Fazer" || novoStatus == "Fazendo" || novoStatus == "Feito") {
        status = std::move(novoStatus);
    }
}

////verifica se a tarefa está vencidaa
//etorna true se a tarefa tem vencimento definido e se o vencimento já passou (vencimento < agora)
bool Tarefa::estaVencida(std::time_t agora) const {
    if (vencimento == 0) return false; //sem prazo -> não é considerada "vencida"
    return vencimento < agora;
}

//verifica se a tarefa está próxima do vencimento segundo o critério do usuário (janelaHoras)
//a tarefa deve ter vencimento definido e estar entre "agora" e "agora + janela"
//exemplo: janelaHoras = 24 -> próximas 24 horas
bool Tarefa::estaProximaDoVencimento(std::time_t agora, int janelaHoras) const {
    if (vencimento == 0) return false; //sem prazo -> não é considerada "próxima de vencimento"
    const std::time_t limite = agora + static_cast<std::time_t>(janelaHoras) * 3600; //converte para segundos multiplicando por 3600
    return (vencimento >= agora) && (vencimento <= limite);
}

//adiciona uma tag à lista, evitando duplicadas
void Tarefa::addTag(std::string tag) {
    //se já existe, não adiciona a mesma tag de novo
    if (std::find(tags.begin(), tags.end(), tag) != tags.end())
        return;
    tags.push_back(std::move(tag));
}

//valida o campo obrigatório (título)
bool Tarefa::validarCampos() const {
    return !titulo.empty();
}

//valida a coerência temporal:
// - Se agendada != 0, ela deve ser no futuro (>= agora)
// - Se vencimento != 0, ele deve ser no futuro (>= agora)
// - Se ambos existem, vencimento não pode ser antes de agendada (vecimento >= agendada)
//0 significa "não informado"
bool Tarefa::validarDatas(std::time_t agora) const {
    if (agendada != 0 && agendada < agora)   return false;
    if (vencimento != 0 && vencimento < agora) return false;
    if (agendada != 0 && vencimento != 0 && vencimento < agendada) return false;
    return true;
}