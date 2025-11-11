#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>


#include "Relogio.h"
#include "RepositorioTarefas.h"
#include "GerenciadorTarefas.h"
#include "DataUtil.h"
#include "Notificador.h"
#include "FiltroCombinado.h"
#include "FiltroPrioridade.h"
#include "FiltroTag.h"
#include "Tarefa.h"
#include "Coluna.h"
#include "Quadro.h"
#include "Usuario.h"


//Funções auxiliares


static void limpaInput() { //limpa o cin e descarta o restante da linha de entrada, para permitir que o programa continue funcionando
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


static std::string perguntarLinha(const std::string& prompt) { //exibe um prompt para o usuário e captura uma linha de texto como entrada (facilita leitura)
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    if (!std::cin) { limpaInput(); }
    return s;
}


static int perguntarInt(const std::string& prompt, int def = 0) { //igual ao anterior, mas captura um número inteiro como entrada
    std::cout << prompt;
    int v;
    std::cin >> v;
    if (!std::cin) { limpaInput(); return def; }
    limpaInput();
    return v;
}


int main() {

    //serviços
    Relogio rel;


    std::string nomeUsuario = perguntarLinha("Digite seu nome: ");
    Usuario usuario(nomeUsuario);
    int horasAntecedencia = perguntarInt("Horas de antecedencia para notificacoes? [padrao=24]: ", 24);
    usuario.definirHorasPreferenciaNotificacao(horasAntecedencia);


    const std::string path = "dados/tarefas.csv";


    #ifdef _WIN32
        system("mkdir dados 2>nul");
    #else
        system("mkdir -p dados");
    #endif


    RepositorioTarefas repo(path);
    GerenciadorTarefas ger(&rel);
    Notificador notif(ger, usuario, &rel);


    //carrega tarefas
    for (const auto& t : repo.carregarTarefas()) {
        try { ger.criarTarefa(t); } catch (...) {}
    }


    while (true) {
        std::cout <<
            "\n===== GERENCIADOR DE TAREFAS (CLI) =====\n"
            "1) Listar quadro Kanban\n"
            "2) Criar tarefa\n"
            "3) Editar tarefa\n"
            "4) Excluir tarefa\n"
            "5) Mover tarefa (A Fazer/Fazendo/Feito)\n"
            "6) Avisos (vencidas/proximas)\n"
            "7) Filtrar tarefas\n"
            "8) Salvar\n"
            "9) Sair\n"
            "Escolha: ";


        int op = 0;
        if (!(std::cin >> op)) { limpaInput(); continue; }
        limpaInput();


        if (op == 1) {
            //monta exibição do quadro a partir do estado atual
            Quadro q = Quadro::construirDe(ger.getTodasTarefas());
            q.exibirQuadro();
            std::cout << "Pendencias: " << ger.contarTarefasPendentes() << "\n";


        } else if (op == 2) {
            std::cout << "\n--- Criar tarefa ---\n";
            const std::string titulo = perguntarLinha("Titulo: ");
            const std::string desc   = perguntarLinha("Descricao: ");
            int prio = perguntarInt("Prioridade (1=Baixa,2=Media,3=Alta,4=Critica) [2]: ", 2);
            std::cout << "Agendada (dd/MM/yyyy HH:mm) [vazio=sem]: ";
            const std::string sag = perguntarLinha("");
            std::time_t ag = converteDataHora(sag);
            std::cout << "Vencimento (dd/MM/yyyy HH:mm) [vazio=sem]: ";
            const std::string sven = perguntarLinha("");
            std::time_t ve = converteDataHora(sven);

            //pergunta ao usuário por tags
            std::string tagInput = perguntarLinha("Digite tags separadas por virgula (deixe em branco para nenhum): ");
            std::vector<std::string> tags;
            if (!tagInput.empty()) {
                std::stringstream ss(tagInput);
                std::string tag;
                while (std::getline(ss, tag, ',')) {
                    tags.push_back(tag);
                }
            }

            Tarefa t(titulo, desc, ag, ve, prio);
            t.setTags(tags);
            std::string erro;
            if (!t.validar(rel.agora(), &erro)) {
                std::cout << "Erro: " << erro << "\n";
            } else {
                ger.criarTarefa(t);
                std::cout << "Criada com ID " << t.getId() << " em 'A Fazer'.\n";
            }


        } else if (op == 3) {
            std::cout << "\n--- Editar tarefa ---\n";
            int id = perguntarInt("ID: ", -1);
            if (id < 0) { std::cout << "ID invalido.\n"; continue; }


            Tarefa atual("", "", 0, 0, 1);
            if (!ger.obterTarefaPorId(id, atual)) {
                std::cout << "Nao encontrada.\n"; continue;
            }


            std::cout << "Deixe vazio para manter.\n";
            const std::string titulo = perguntarLinha("Novo titulo: ");
            const std::string desc   = perguntarLinha("Nova descricao: ");
            int prio = perguntarInt("Nova prioridade (1..4, 0=manter): ", 0);


            std::cout << "Nova agendada (dd/MM/yyyy HH:mm) [vazio=manter]: ";
            const std::string sag = perguntarLinha("");
            std::cout << "Novo vencimento (dd/MM/yyyy HH:mm) [vazio=manter]: ";
            const std::string sven = perguntarLinha("");


            Tarefa edit = atual;
            if (!titulo.empty()) edit.setTitulo(titulo);
            if (!desc.empty())   edit.setDescricao(desc);
            if (prio != 0)       edit.setPrioridade(prio);
            if (!sag.empty())    edit.setAgendada(converteDataHora(sag));
            if (!sven.empty())   edit.setVencimento(converteDataHora(sven));


            try {
                ger.editarTarefa(id, edit);
                std::cout << "Tarefa " << id << " editada.\n";
            } catch (const std::exception& e) {
                std::cout << "Erro: " << e.what() << "\n";
            }


        } else if (op == 4) {
            std::cout << "\n--- Excluir tarefa ---\n";
            int id = perguntarInt("ID: ", -1);
            if (id < 0) { std::cout << "ID invalido.\n"; continue; }
            const std::string conf = perguntarLinha("Confirma (s/N)? ");
            if (!conf.empty() && (conf[0] == 's' || conf[0] == 'S')) {
                ger.excluirTarefa(id);
                std::cout << "Excluida.\n";
            } else std::cout << "Cancelado.\n";


        } else if (op == 5) {
            std::cout << "\n--- Mover tarefa ---\n";
            int id = perguntarInt("ID: ", -1);
            if (id < 0) { std::cout << "ID invalido.\n"; continue; }
            const std::string novo = perguntarLinha("Novo status (A Fazer/Fazendo/Feito): ");
            ger.moverTarefa(id, novo);
            std::cout << "Movida.\n";


        } else if (op == 6) {
            notif.exibirAvisos();


        } else if (op == 7) {
            std::cout << "\n--- Filtrar tarefas ---\n";
    
            // Pergunta ao usuário o que ele quer filtrar
            std::cout << "Escolha um ou mais criterios de filtro:\n";
            std::cout << "1) Filtrar por tag\n";
            std::cout << "2) Filtrar por prioridade\n";
            int filtroEscolhido1 = perguntarInt("Escolha o primeiro criterio: ", 0);

            
            std::vector<std::shared_ptr<EstrategiaFiltro>> filtros;
            
            if (filtroEscolhido1 == 1) {
                std::string tag = perguntarLinha("Digite a tag para filtrar: ");
                filtros.push_back(std::make_shared<FiltroTag>(tag));  // Filtro por tag
            } else if (filtroEscolhido1 == 2) {
                int prioridade = perguntarInt("Digite a prioridade para filtrar (1-4): ");
                filtros.push_back(std::make_shared<FiltroPrioridade>(prioridade));  // Filtro por prioridade
            }

             //pergunta ao usuário se ele quer adicionar um segundo filtro
            std::cout << "Deseja adicionar um segundo filtro? (1) Sim (2) Não: ";
            int adicionarFiltro = perguntarInt("", 0);
            if (adicionarFiltro == 1) {
                std::cout << "Escolha o segundo criterio de filtro:\n";
                std::cout << "1) Filtrar por tag\n";
                std::cout << "2) Filtrar por prioridade\n";
                int filtroEscolhido2 = perguntarInt("Escolha o segundo criterio: ", 0);

                if (filtroEscolhido2 == 1) {
                    std::string tag = perguntarLinha("Digite a tag para filtrar: ");
                    filtros.push_back(std::make_shared<FiltroTag>(tag));  // Filtro por tag
                } else if (filtroEscolhido2 == 2) {
                    int prioridade = perguntarInt("Digite a prioridade para filtrar (1-4): ");
                    filtros.push_back(std::make_shared<FiltroPrioridade>(prioridade));  // Filtro por prioridade
                }
            }
            
            //aplica os filtros
            ger.aplicarFiltros(filtros);

        } else if (op == 8) {
            try {
                repo.arquivoBackup();
                repo.salvarTarefa(ger.getTodasTarefas());
                std::cout << "Salvo em '" << path << "'. Backup em '" << path << ".bak'.\n";
            } catch (const std::exception& e) {
                std::cout << "Erro ao salvar: " << e.what() << "\n";
            }


        } else if (op == 9) {
            try { repo.arquivoBackup(); repo.salvarTarefa(ger.getTodasTarefas()); } catch (...) {}
            break;


        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
    return 0;

}
