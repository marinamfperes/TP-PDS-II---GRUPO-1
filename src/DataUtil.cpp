/**
 * @file DataUtil.cpp
 * @brief Implementações das funções utilitárias de data e hora.
 */

#include "DataUtil.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

//Helpers de data e tempo

//converte string "dd/MM/yyyy (data) HH:mm (hora e minutos)" para tipo time_t (0 se vazio) -> pega o texto que indica a data e horário e transforma em um tipo que o programa entende
//time_t é número de segundos desde 01/01/1970
std::time_t converteDataHora(const std::string& s) {
    if (s.empty()) return 0; //se usuário deixou em branco => sem data (0)
    std::tm tm{}; //estrutura definida na biblioteca <ctime> usada para representar uma data e hora; começa vazia
    tm.tm_isdst = -1; //deixa horário de verão “desconhecido”, quando não sabemos se ele está em vigor ou não; sistema realiza essa verificação automaticamente
    std::istringstream iss(s); //cria stream a partir da string
    iss >> std::get_time(&tm, "%d/%m/%Y %H:%M"); //tenta ler no formato completo
    if (!iss.fail()) {
        return std::mktime(&tm); //se a string contiver uma data válida, a função converte tm e retorna um valor time_t correspondente
    }
    //tenta ler só data "dd/MM/yyyy"
    std::istringstream iss2(s); //novo stream (o anterior falhou)
    iss2 >> std::get_time(&tm, "%d/%m/%Y"); //lê só a data
    if (!iss2.fail()) {
        return std::mktime(&tm); //retorna meia-noite daquela data
    }
    return 0; //se tudo falhar, retorna 0 (sem data)
}

//converte tipo time_t para string "dd/MM/yyyy HH:mm" (ou "—" se a data não for definida/0)
std::string formataDataHora(std::time_t ts) {
    if (ts == 0) return "—";
    std::tm* lt = std::localtime(&ts); //converte a hora para o fuso horário local e preenche os campos da estrutura tm com as informações legíveis da data e hora; retona um ponteiro para essa estrutura
    char buf[32]; //buffer de caracteres onde a data formatada será armazenada
    if (lt && std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", lt)) { //função strftime converte a estrutura tm para uma string formatada; 1 arg é o buffer onde a data formatada será armazenada;2 arg é o tamanho do buffer; 3 arg é o formato desejado da data e hora; 4 arg é o ponteiro para a estrutura tm contendo os dados da data
        return std::string(buf); // se a conversão funcionar, retorna a string formatada armazenada em buf
    }
    return std::to_string(static_cast<long long>(ts));
}
