/**
 * @file DataUtil.h
 * @brief Funções auxiliares para conversão e formatação de datas e horários.
 *
 * Este arquivo define funções que convertem datas em strings no formato
 * "dd/MM/yyyy HH:mm" para o tipo `time_t` e vice-versa, usadas em todo o
 * sistema de gerenciamento de tarefas.
 */

#ifndef DATAHORAUTIL_H
#define DATAHORAUTIL_H

#include <string>
#include <ctime>

bool validaDataHora(const std::string& s);

/**
 * @brief Converte uma string no formato "dd/MM/yyyy HH:mm" para um valor `time_t`.
 * @param s String representando data e hora.
 * @return Valor `time_t` correspondente, ou 0 se a string estiver vazia ou inválida.
 */
std::time_t converteDataHora(const std::string& s);

/**
 * @brief Converte um valor `time_t` para string no formato "dd/MM/yyyy HH:mm".
 * @param ts Valor `time_t` a ser convertido.
 * @return String formatada com a data e hora, ou "—" se o valor for 0.
 */
std::string formataDataHora(std::time_t ts);

#endif
