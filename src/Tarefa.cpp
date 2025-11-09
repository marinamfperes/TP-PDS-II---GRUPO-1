#include "Tarefa.h"
#include <stdexcept>   //para lançar exceções em validações
#include <algorithm>   //para algoritmos de busca/remoção -> std::find

//gerador simples de IDs únicos
//"static" garante um contador único para todas as Tarefas
//cada nova Tarefa recebe id = GERADOR_ID_TAREFA++
static int GERADOR_ID_TAREFA = 1;

//construtor que inicializa todos os campos
Tarefa::Tarefa(std::string titulo,
               std::string descricao,
               std::time_t agendada,
               std::time_t vencimento,
               int prioridade)
    : id(GERADOR_ID_TAREFA++), //gera id único e incrementa o contator
      titulo_(std::move(titulo)),
      descricao_(std::move(descricao)),
      agendada_(agendada),
      vencimento_(vencimento),
      prioridade_(prioridade),
      status_("A Fazer") //status inicial padrão do quadro Kanban
{}

void Tarefa::setIdParaCarga(int novoId) {
    id = novoId;
}

void Tarefa::ajustarProximoId(int proximoVal) {
    //evita “voltar” contador — só aumenta
    if (proximoVal > proximoId_) proximoId_ = proximoVal;
}

//getters (acessam dados internos sem permitir modificação)
int Tarefa::getId() const { return id; }
const std::string& Tarefa::getTitulo() const { return titulo_; }
const std::string& Tarefa::getDescricao() const { return descricao_; }
std::time_t Tarefa::getAgendada() const { return agendada_; }
std::time_t Tarefa::getVencimento() const { return vencimento_; }
int Tarefa::getPrioridade() const { return prioridade_; }
const std::string& Tarefa::getStatus() const { return status_; }
const std::vector<std::string>& Tarefa::getTags() const { return tags_; }

//setters
void Tarefa::setTitulo(const std::string& novo) { titulo_ = novo; }
void Tarefa::setDescricao(const std::string& novo) { descricao_ = novo; }
void Tarefa::setAgendada(std::time_t ts) { agendada_ = ts; }
void Tarefa::setVencimento(std::time_t ts) { vencimento_ = ts; }
void Tarefa::setPrioridade(int p) { prioridade_ = p; }

//troca o status textual da tarefa no Kanban
// aceita só "A Fazer", "Fazendo" ou "Feito"
void Tarefa::atualizarStatus(const std::string& novoStatus) {
    if (novoStatus == "A Fazer" || novoStatus == "Fazendo" || novoStatus == "Feito") {
        status_ = novoStatus;
    }
}

//TAGS

//adiciona uma tag à lista, evitando duplicadas
void Tarefa::addTag(const std::string& tag) {
    if (tag.empty()) return;
    auto it = std::find(tags_.begin(), tags_.end(), tag);
    if (it == tags_.end()) tags_.push_back(tag);
}

void Tarefa::clearTags() {
    tags_.clear();
}

//remove uma tag
bool Tarefa::removeTag(const std::string& tag) {
    auto it = std::find(tags_.begin(), tags_.end(), tag);
    if (it == tags_.end()) return false;
    tags_.erase(it);
    return true;
}

//ESTADO TEMPORAL

////verifica se a tarefa está vencida
//etorna true se a tarefa tem vencimento definido e se o vencimento já passou (vencimento < agora)
bool Tarefa::estaVencida(std::time_t agora) const {
    if (vencimento_ == 0) return false; //sem prazo -> não é considerada "vencida"
    return vencimento_ < agora;
}

//verifica se a tarefa está próxima do vencimento segundo o critério do usuário (janelaHoras)
//a tarefa deve ter vencimento definido e estar entre "agora" e "agora + janela"
//exemplo: janelaHoras = 24 -> próximas 24 horas
bool Tarefa::estaProximaDoVencimento(std::time_t agora, int janelaHoras) const {
    if (vencimento_ == 0) return false; //sem prazo -> não é considerada "próxima de vencimento"
    const std::time_t limite = agora + static_cast<std::time_t>(janelaHoras) * 3600; //converte para segundos multiplicando por 3600
    return (vencimento_ >= agora) && (vencimento_ <= limite);
}

//VALIDAÇÕES

//valida o campo obrigatório (título)
bool Tarefa::validarCampos() const {
    return !titulo_.empty();
}

//valida a coerência temporal:
// - Se agendada != 0, ela deve ser no futuro (>= agora)
// - Se vencimento != 0, ele deve ser no futuro (>= agora)
// - Se ambos existem, vencimento não pode ser antes de agendada (vecimento >= agendada)
//0 significa "não informado"
bool Tarefa::validarDatas(std::time_t agora) const {
    if (agendada_ != 0 && agendada_ < agora)   return false; //agendada no passado
    if (vencimento_ != 0 && vencimento_ < agora) return false; //vencimento no passado
    if (agendada_ != 0 && vencimento_ != 0 && vencimento_ < agendada_) return false; //incoerente
    return true;
}

//unifica as validações
bool Tarefa::validar(std::time_t agora, std::string* erro) const {
    if (!validarCampos()) {
        if (erro) *erro = "Título é obrigatório.";
        return false;
    }
    if (!validarDatas(agora)) {
        if (erro) *erro = "Datas incoerentes: não podem estar no passado e o vencimento não pode ser anterior à data agendada.";
        return false;
    }
    return true;
}