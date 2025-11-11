#ifndef REPOSITORIO_TAREFAS_H
#define REPOSITORIO_TAREFAS_H


#include "Tarefa.h"
#include <vector>
#include <string>


class RepositorioTarefas {
private:
    // repositorio sabera em qual arquivo deve salvar
    std::string arquivo_;
    static int proximoId_; // variável para armazenar o próximo ID


public:

    // Métodos para salvar e carregar o próximo ID
    static void salvarProximoId(int proximoId);
    static int carregarProximoId();
    static int obterEIncrementarProximoId();

    // Construtor para definir o arquivo de persistência
    RepositorioTarefas(const std::string& nomeArquivo);


    // Salvar tarefas em arquivo
    void salvarTarefa(const std::vector<Tarefa>& tarefas) const;


    // Carrega a lista de tarefas do banco de dados ou arquivo
    std::vector<Tarefa> carregarTarefas() const;


    //função para fazer backup do arquivo
    void arquivoBackup() const;


};


#endif
