# TP PDS II - GRUPO 1
GERENCIADOR DE TAREFAS PARA ESTUDANTES

Integrantes: Daniel Sales, Luísa Gouthier, Marina Fonseca e Miguel Del Corsi

O projeto do Trabalho Prático da disciplina de Programação e Desenvolvimento de Software II, desenvolvido pelo Grupo 1, tem como finalidade o desenvolvimento de um gerenciador de tarefas voltado para estudantes, visando otimizar a rotina universitária a partir de uma ferramenta organizacional prática e eficiente. O comando do projeto propõe a criação de um sistema de porte médio (aproximadamente 1000 linhas), com o propósito de consolidar os conhecimentos adquiridos sobre a linguagem C++ ao longo do segundo semestre de 2025.

A proposta busca minimizar problemas comuns entre alunos, como a má administração do tempo e dos compromissos, fatores que frequentemente resultam em conflitos de horário, atrasos na entrega de trabalhos e ausências em aulas.

Tendo em vista as problemáticas evidenciadas, o sistema tem como objetivo macro otimizar o gerenciamento das tarefas diárias, permitindo que o usuário as organize e priorize de maneira intuitiva, personalizada e dinâmica. Para isso, o projeto será baseado na metodologia Kanban, um modelo visual de gerenciamento de tarefas que facilita a organização e o controle do progresso das atividades. Na metodologia Kanban, as tarefas são representadas por cartões que são movidos entre diferentes colunas de acordo com o estágio em que se encontram. Essa abordagem permitirá ao estudante visualizar de forma clara o que precisa ser feito, o que está em andamento e o que já foi concluído.

Enquanto isso, os micro objetivos do projeto consistem em:

- Implementar as funcionalidades de cadastro, edição e exclusão de tarefas;
- Permitir a classificação, filtragem e priorização das tarefas com critérios como horário e data de realização e de vencimento (prazo), importância, categorias personalizadas;
- Incluir quadro Kanban para visualização das tarefas com colunas como "A Fazer", "Fazendo" e "Feito";
- Destacar as tarefas que não foram concluídas no prazo ou estão próximas do vencimento;
- Exibir um contador de tarefas com a quantidade de tarefas pendentes;
- Desenvolver uma interface intuitiva, de acordo com o perfil do público estudantil.

Como resultado, espera-se que o projeto desenvolvido seja capaz de proporcionar aos estudantes uma gestão mais eficiente e organizada de suas tarefas acadêmicas, melhorando sua produtividade e redução do estresse relacionado ao cumprimento de prazos. A utilização do Kanban facilitará a visualização do progresso das atividades, contribuindo para o controle de compromissos e evitando atrasos. Além disso, o sistema proporcionará a personalização das tarefas conforme a necessidade individual de cada aluno, criando uma ferramenta flexível e adaptada ao perfil universitário.

============================================================================

INFORMAÇÕES ESSENCIAIS 

-> Obs.: Existem divergências entre o escopo inicial (que não fora editado para fins de correção) e a entrega final do projeto, isso fica mais claro ao longo dos tópicos subsequentes.
  
- COMPILAÇÃO E EXECUÇÃO:


- ARQUITETURA DO PROJETO: Como pode ser visualizado na imagem abaixo, nosso trabalho fora seccionado em cinco pastas principais: build, docs, include, src, tests.
    - VSCODE: configurações do .json para compilação e execução do projeto;
    - BUILD: arquivos gerados durante a compilação, como o executável final main.exe;
    - DOCS: documentos do projeto, como os Cartões CRC e os User Stories, além dos arquivos gerados pelo Doxygen;
    - INCLUDE: arquivos de cabeçalho (.h), onde estão as declarações de classes e structs, como Coluna.h;
    - SRC: onde está localizado o código principal, alocando as implementações das funções declaradas em "include", como Coluna.cpp;
    - TESTS: arquivos de teste que comprovam a funcionalidade do código.

<img width="345" height="365" alt="image" src="https://github.com/user-attachments/assets/a9726a5e-e525-4d0c-8b5f-89a46dbdeb93" />



- FUNCIONALIDADES ENTREGUES: Nosso projeto possui, como objetivo principal, melhorar a experiência dos estudantes na Universidade, sendo assim, projetamos um quadro Kanban para organização. Com esse intuito, as principais funcionalidades entregues foram:
    - Adição de atividades no escopo e classificação por prioridade;
    - Cadastro, edição e exclusão de tarefas;
    - Notificações quando a atividade programada está chegando ao prazo de vencimento;
    - Organização das atividades entre "A fazer", "Fazendo", "Feito";
    - Contagem de tarefas pendentes.


- INSTRUÇÕES DE USO: Para utilizar o programa, é necessário, primeiramente, se registrar e incluir a data do dia. Depois, um menu é exibido a fim de que o usuário escolha a funcionalidade que ele deseja seguir (ex. se ele deseja cadastrar uma tarefa, digita o número referente a essa funcionalidade e depois preenche as informações de acordo com o que é solicitado pelo programa).


- TRATAMENTO DE EXCEÇÕES E PROGRAMAÇÃO DEFENSIVA:


- DOXYGEN: https://marinamfperes.github.io/TP-PDS-II---GRUPO-1/
  

- VÍDEO DA COMPILAÇÃO E DA EXECUÇÃO:
  

- SOBRE A EQUIPE: Nosso projeto foi extremamente dividido, objetivando que todos tivessem contribuído, ao menos um pouco, com cada etapa de desenvolvimento do código. A baixo estão as principais atividades que cada membro do grupo executou:
    - Daniel Sales: Notificador.h, Relogio.h, RepositorioTarefas.h, FiltroCombinado.cpp, FiltroPrioridade.cpp, FiltroTag.cpp,  adições no README;
 
    - Luísa Gouthier: modelagem inicial (CRC), DataUtil.h, FiltroPrioridade.h, FiltroCombinado.h, GerenciadorTarefas.h/GerenciadorTarefas.cpp, Notificador.cpp, Tarefa.h/Tarefa.cpp, main.cpp, correção de erros (compatilibilidade entre todos os arquivos .h e .cpp);
 
    - Marina Fonseca: escopo inicial do projeto, requisitos (User Stories), DataUtil.cpp, FiltroTag.cpp, Coluna.h/Coluna.cpp, EstrategiaFiltro.h/EstrategiaFiltro.cpp, Quadro.h/Quadro.cpp, adições no README;
      
    - Miguel Del Corsi: Usuario.h, Relogio.cpp, RepositorioTarefas.cpp, Usuario.h/Usuario.cpp,  adições no README, Doxygen;
 

- CICLO DE DESENVOLVIMENTO E LINHA DO TEMPO DAS SPRINTS:
  ![TimelineCycle](https://github.com/user-attachments/assets/03b2edba-5cc3-49e4-ad31-68ea456fc3cc)


- PLANEJADO x EXECUTADO:
  - Implementar as funcionalidades de cadastro, edição e exclusão de tarefas; ✔️
 
  - Permitir a classificação, filtragem e priorização das tarefas com critérios como horário e data de realização e de vencimento (prazo), importância, categorias personalizadas; ✔️
    
  - Incluir quadro Kanban para visualização das tarefas com colunas como "A Fazer", "Fazendo" e "Feito"; ️✖️✔️ -> As categorias de "A Fazer", "Fazendo" e "Feito" foram feitas, mas a visualização no Kanban não foi feita, tendo em vista que não adotamos interface gráfica.
    
  - Destacar as tarefas que não foram concluídas no prazo ou estão próximas do vencimento; ️️✔️
    
  - Exibir um contador de tarefas com a quantidade de tarefas pendentes; ✔️
    
  - Desenvolver uma interface intuitiva, de acordo com o perfil do público estudantil. ✖️ -> Percebemos que a montagem de interface gráfica, a partir do programa Qt, seria muito complexa e despendiria muito tempo. Ajustar o Github, bem como VsCode, e alinhar tudo seria mais do que conseguiríamos fazer.


- EVIDÊNCIAS NO GITHUB: (obs.: constam cinco autores, mas dois são da mesma autora, Luisa Gouthier)
  <img width="1347" height="763" alt="image" src="https://github.com/user-attachments/assets/d2e8ef8a-f10e-4da8-84d5-40d7983c7a4a" />
  <img width="1836" height="389" alt="image" src="https://github.com/user-attachments/assets/21b02849-4655-44c7-b89f-fde3383bd8cf" />




- AGRADECIMENTOS: Gostaríamos de expressar nossos agradecimentos a todas as ferramentas, plataformas e pessoas que contribuíram, direta ou indiretamente, para o desenvolvimento deste trabalho.
    - Agradecemos ao professor Thiago Noronha, pela orientação, disponibilidade e pelos ensinamentos transmitidos ao longo da disciplina, que foram fundamentais para a construção e consolidação dos conhecimentos aplicados neste projeto;
      
    - Agradecemos também ao GitHub, por oferecer uma plataforma robusta de versionamento, colaboração e hospedagem de código, essencial para o gerenciamento do projeto e para a publicação da documentação gerada;
      
    - Ao Visual Studio Code (VS Code), pela praticidade, integração com Git e suporte a múltiplas linguagens, que facilitaram significativamente o processo de desenvolvimento e depuração do código;
      
    - Ao Doxygen, pela geração automatizada da documentação do código-fonte, garantindo organização, rastreabilidade e clareza na estrutura do projeto;
      
    - Aos colegas de equipe, pela dedicação, comprometimento e colaboração em todas as etapas do desenvolvimento, desde o planejamento até a entrega final.
