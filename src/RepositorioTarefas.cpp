#include "RepositorioTarefas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <filesystem>
#include <stdexcept>


RepositorioTarefas::RepositorioTarefas(const std::string& nomeArquivo)
    : arquivo_(nomeArquivo) {
            Tarefa::carregarIdGerador();
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
    }


    in.close();
    return tarefas;
}


void RepositorioTarefas::arquivoBackup() const {
    try {
        if (!std::filesystem::exists(arquivo_)) return; // Se o arquivo não existe, não faz nada
        const std::string bak = arquivo_ + ".bak";  // Nome do arquivo de backup
        std::filesystem::copy_file(arquivo_, bak, std::filesystem::copy_options::overwrite_existing);
    } catch (...) {
        std::cerr << "Erro ao criar backup do arquivo.\n";
    }
}
