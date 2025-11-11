#include "RepositorioTarefas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdio> //para std::remove, std::rename
#include <stdexcept>

int RepositorioTarefas::proximoId_ = 1;  // Inicializando com o valor 1

// Carrega o próximo ID a partir do arquivo
void RepositorioTarefas::salvarProximoId(int proximoId) {
    std::ofstream idArquivo("proximo_id.txt");
    if (!idArquivo.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo para salvar o próximo ID.");
    }
    idArquivo << proximoId;
    idArquivo.close();
}

// Carrega o próximo ID do arquivo
int RepositorioTarefas::carregarProximoId() {
    std::ifstream idArquivo("proximo_id.txt");
    if (idArquivo.is_open()) {
        idArquivo >> proximoId_;
        idArquivo.close();
    }
    return proximoId_;
}

RepositorioTarefas::RepositorioTarefas(const std::string& nomeArquivo)
    : arquivo_(nomeArquivo) {
        // Carrega o próximo ID ao inicializar o repositório
    proximoId_ = carregarProximoId();
    }

//Método para acessar e incrementar o próximo ID
int RepositorioTarefas::obterEIncrementarProximoId() {
    int idAtual = proximoId_++;
    salvarProximoId(proximoId_);  // Salva o próximo ID após incrementar
    return idAtual;
}


// Salva todas as tarefas em um arquivo de texto simples
void RepositorioTarefas::salvarTarefa(const std::vector<Tarefa>& tarefas) const {
    std::ofstream out(arquivo_);
    if (!out.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo para salvar: " + arquivo_);
    }


    for (const auto& t : tarefas) {
        out << t.getId() << ';'
            << t.getTitulo() << ';'
            << t.getDescricao() << ';'
            << static_cast<long long>(t.getAgendada()) << ';'
            << static_cast<long long>(t.getVencimento()) << ';'
            << t.getPrioridade() << ';'
            << t.getStatus() << '\n';
    }


    out.close();
    // Salva o próximo ID após salvar as tarefas
    salvarProximoId(proximoId_);
}


// Carrega as tarefas a partir do arquivo
std::vector<Tarefa> RepositorioTarefas::carregarTarefas() const {
    std::vector<Tarefa> tarefas;
    std::ifstream in(arquivo_);
    if (!in.is_open()) {
        std::cerr << "Aviso: arquivo " << arquivo_ << " não encontrado. Nenhuma tarefa carregada.\n";
        return tarefas;
    }


    std::string linha;
    while (std::getline(in, linha)) {
        std::istringstream ss(linha);
        std::string campo;
        std::vector<std::string> campos;
        while (std::getline(ss, campo, ';')) {
            campos.push_back(campo);
        }


        if (campos.size() < 7) continue;  // Ignora linhas com dados incompletos


        int id = std::stoi(campos[0]);
        std::string titulo = campos[1];
        std::string descricao = campos[2];
        std::time_t agendada = static_cast<std::time_t>(std::stoll(campos[3]));
        std::time_t vencimento = static_cast<std::time_t>(std::stoll(campos[4]));
        int prioridade = std::stoi(campos[5]);
        std::string status = campos[6];


        Tarefa t(titulo, descricao, agendada, vencimento, prioridade);
        t.atualizarStatus(status);
        tarefas.push_back(t);

        // Atualiza o próximo ID
        if (t.getId() >= proximoId_) {
            proximoId_ = t.getId() + 1;
        }
    }


    in.close();
    return tarefas;
}


void RepositorioTarefas::arquivoBackup() const {
    std::ifstream src(arquivo_, std::ios::binary);
    if (!src.is_open()) {
        return;  //se o arquivo não existe, não faz nada
    }

    std::string bak = arquivo_ + ".bak";

    std::ofstream dest(bak, std::ios::binary); 
    if (!dest.is_open()) {
        std::cerr << "Erro ao criar backup do arquivo.\n";
        return;
    }

    dest << src.rdbuf();  //copia todo o conteúdo

    src.close();
    dest.close();
}
