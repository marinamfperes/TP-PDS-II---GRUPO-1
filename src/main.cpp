#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "Relogio.h"
#include "RepositorioTarefas.h"
#include "GerenciadorTarefas.h"
#include "Notificador.h"
#include "Tarefa.h"
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


return 0;


}
