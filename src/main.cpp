#include <QApplication> //gerencia o ciclo de vida da aplicação (inicialização, eventos, encerramento)

//argc e argv são parâmetros usados para capturar argumentos de linha de comando e são repassados ao QApplication, que pode utilizá-los internamente.

int main(int argc, char *argv[]) {
    //instancia o objeto QApplication, que é obrigatório em qualquer programa Qt, pois gerencia toda a parte de interface gráfica, controle de eventos, interação com o sistema operacional, e o loop de execução da aplicação.
    QApplication app(argc, argv);


    //o método exec() bloqueia o código até o encerramento da aplicação, garantindo que tudo continue funcionando enquanto a janela estiver aberta.
    return app.exec();
}
