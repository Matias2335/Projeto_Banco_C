#include <stdio.h>
#include <string.h>
#include <time.h>

struct gasto {
  float valor;
  char descricao[200];
  int dia;
  int mes;
  int ano;
  char categoria[50];
};

struct comparador_string_categoria {
  char nome_categoria[20];
};

int main(void) {
  int investir;
  float valor_investir;
  int escolher;
  int escolha;
  float calc;
  float total;
  float cotas;
  int retorno_leitura;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  int ano = tm.tm_year + 1900;
  int mes = tm.tm_mon + 1;
  int dia = tm.tm_mday;

  printf("\n- MENU DE OPÇÕES -\n");
  printf("1 - Cadastro de receitas e gastos\n");
  printf("2 - Relatório (12 meses)\n");
  printf("3 - Relatório (último mês)\n");
  printf("4 - Investimento\n");
  printf("5 - Conta Corrente\n");
  printf("0 - Sair\n");
  printf("\nDigite a opção desejada: ");
  scanf("%d", &escolha);
  printf("\n");

  // Cadastro de receita e gasto
  if (escolha == 1) {
    struct gasto Novo;
    char descricao[200];
    char categoria[50];

    printf("Digite o valor do gasto: ");
    scanf("%f", &Novo.valor);

    printf("Digite a descrição do gasto: ");
    scanf("%s", descricao);
    for (int i = 0; i < 20; i++) {
      Novo.descricao[i] = descricao[i];
    }

    printf("Digite o dia do gasto: ");
    scanf("%d", &Novo.dia);

    printf("Digite o mês do gasto: ");
    scanf("%d", &Novo.mes);

    printf("Digite o ano do gasto: ");
    scanf("%d", &Novo.ano);

    printf("Digite a categoria do gasto: ");
    scanf("%s", categoria);
    for (int i = 0; i < 20; i++) {
      Novo.categoria[i] = categoria[i];
    }

    FILE *arquivo_write = fopen("gasto.txt", "ab");
    fwrite(&Novo, sizeof(struct gasto), 1, arquivo_write);
    fclose(arquivo_write);

    printf("\n- GASTO CADASTRADO -\n");
    main();

  }
  // Relatório - últimos 12 meses
  else if (escolha == 2) {
    struct gasto Anual;

    FILE *arquivo_read = fopen("gasto.txt", "rb");
    FILE *arquivo_anual = fopen("relatorioAnual.txt", "w");

    do {
      retorno_leitura = fread(&Anual, sizeof(struct gasto), 1, arquivo_read);

      if (retorno_leitura == 0) {
        break;
      } else if ((Anual.ano == ano && Anual.mes <= mes) ||
                 (Anual.ano < ano && Anual.mes >= mes)) {
        fprintf(arquivo_anual, "Valor: %.2f\n", Anual.valor);
        fprintf(arquivo_anual, "Descrição: %s\n", Anual.descricao);
        fprintf(arquivo_anual, "Dia: %d\n", Anual.dia);
        fprintf(arquivo_anual, "Mês: %d\n", Anual.mes);
        fprintf(arquivo_anual, "Ano: %d\n", Anual.ano);
        fprintf(arquivo_anual, "Categoria: %s\n\n", Anual.categoria);
      }
    } while (retorno_leitura != 0);

    fclose(arquivo_anual);
    fclose(arquivo_read);

    printf("- RELATÓRIO DE 12 MESES CRIADO -\n");
    main();

  }
  // Relatório - último mês por categoria
  else if (escolha == 3) {
    struct gasto Categoria;
    struct comparador_string_categoria category;
    int mes_anterior = mes - 1;

    FILE *arquivo_read = fopen("gasto.txt", "rb");
    FILE *cat_mensal = fopen("relatorioCategoria.txt", "w");

    printf("Digite a categoria: ");
    scanf("%s", category.nome_categoria);

    do {
      retorno_leitura =
          fread(&Categoria, sizeof(struct gasto), 1, arquivo_read);

      if (retorno_leitura == 0) {
        break;
      } else if (mes_anterior == Categoria.mes && ano == Categoria.ano) {
        int categorias_iguais =
            strcmp(category.nome_categoria, Categoria.categoria);

        if (categorias_iguais == 0) {
          fprintf(cat_mensal, "Valor: %.2f\n", Categoria.valor);
          fprintf(cat_mensal, "Descrição: %s\n", Categoria.descricao);
          fprintf(cat_mensal, "Dia: %d\n", Categoria.dia);
          fprintf(cat_mensal, "Mês: %d\n", Categoria.mes);
          fprintf(cat_mensal, "Ano: %d\n", Categoria.ano);
          fprintf(cat_mensal, "Categoria: %s\n\n", Categoria.categoria);
        }
      }
    } while (retorno_leitura != 0);

    fclose(arquivo_read);
    fclose(cat_mensal);

    printf("\n- RELATÓRIO MENSAL DE CATEGORIA CRIADO-\n");
    main();
  }
  // Investimento
  else if (escolha == 4) {
    printf("1 - Renda Fixa\n");
    printf("2 - Fundos\n");
    printf("3 - Renda Variável\n");
    printf("4 - Previdência Privada\n");
    printf("5 - Tesouro Direto\n");
    printf("6 - Poupança\n");
    printf("7 - COE\n");
    printf("0 - Voltar\n");

    printf("\nQual deseja investir: ");
    scanf("%d", &investir);

    // Investimentos que peguei do banco inter na parte de Renda Fixa(tudo real
    // nada inventado)
    if (investir == 1) {
      printf("\n1 - LCI IPCA FINAL 3 ANOS\n");
      printf("2 - CDB LIQUIDEZ DIARIA\n");
      printf("3 - CDB VOITER\n");
      printf("4 - ENERGISA\n");
      printf("0 - Sair\n");

      printf("\nDigite qual lugar deseja aplicar seu dinheiro: ");
      scanf("%d", &escolher);

      // IPCA é a inflação do mes tirei uma media durante 12 meses para
      // calcular
      if (escolher == 1) {
        printf("\nDescrição sobre LCI IPCA FINAL 3 ANOS\n");
        printf("Grau de risco: Baixo\nRentabilidade: A partir de 4.41%% + "
               "IPCA\nValor Minimo: R$50,00\nVencimento 23/10/2025\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.0714 + 0.0441) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 2) {
        printf("\nDescrição sobre CDB LIQUIDEZ DIARIA");
        printf("\nGrau de risco: Muito baixo\nRentabilidade: A partir de "
               "98.0%% do "
               "CDI\nValor Minimo:R$100,00\nVencimento 08/10/2024\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.1167) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 3) {
        printf("\nDescrição sobre CDB VOITER");
        printf("\nGrau de risco: Médio\nRentabilidade: 14,25%% a.a\nValor "
               "Minimo:R$1001,45\nVencimento 18/11/2024\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.1425) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 4) {
        printf("\nDescrição sobre ENERGISA");
        printf("\nGrau de risco: Alto\nRentabilidade: IPCA + 6.00%% a.a\nValor "
               "Minimo: R$1008,45\nVencimento 15/04/2029");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.0714 + 0.06) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 0) {
        main();
      }
    }

    // Lista de investimentos em fundos imobiliarios

    if (investir == 2) {
      printf("\n1 - Inter Inflação Conservador FIRF CP\n");
      printf("2 - AZ Quest Luce FIC FIRF CP LP\n");
      printf("3 - Inter ACess Absolute Vertex FIC FIM\n");
      printf("4 - Asa Hedge FIC FIM\n");
      printf("0 - Sair\n");

      printf("\nDigite qual lugar deseja aplicar seu dinheiro: ");
      scanf("%d", &escolher);

      if (escolher == 1) {
        printf("\nDescrição sobre Inter Conservador FIRF CP");
        printf(
            "\nGrau de risco: Baixo\nRentabilidade: 12,59%% a.a\nValor Minimo: "
            "R$500,00\nData inicial 30/01/2015");
        printf("\nDigite quantos reais deseja investir:");
        scanf("%f", &valor_investir);
        calc = (0.1259) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 2) {
        printf("\nDescrição sobre Inter ACess Absolute Vertex FIC FIM");
        printf(
            "\nGrau de risco: Baixo\nRentabilidade: 12,27%% a.a\nValor Minimo: "
            "R$500,00\nData inicial 11/12/2015");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.1227) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 3) {
        printf("\nDescrição sobre AZ Quest Luce FIC FIRF CP LP");
        printf(
            "\nGrau de risco: Medio\nRentabilidade: 24,94%% a.a\nValor Minimo: "
            "R$500,00\nData inicial 01/09/2014");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.2494) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 4) {
        printf("\nDescrição sobre AZ Quest Luce FIC FIRF CP LP");
        printf(
            "\nGrau de risco: Alto\nRentabilidade: 40,07%% a.a\nValor Minimo: "
            "R$10.000,00\nData inicial 01/09/2014");
        printf("\nDigite quantos reais deseja investir:");
        scanf("%f", &valor_investir);
        calc = (0.4007) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 0) {
        main();
      }
    }
    // investimentos em algumas acoes populares atualmente
    if (investir == 3) {
      printf("\n1 - BBAS3\n");
      printf("2 - SANB11\n");
      printf("3 - PETR4\n");
      printf("4 - VALE3\n");
      printf("0 - Sair\n");
      printf("\nDigite qual lugar deseja aplicar seu dinheiro: ");
      scanf("%d", &escolher);
      switch (escolher) {
      case 1:
        printf("\nDescrição sobre BBAS3\n");
        printf("Grau de Risco: Alto\nRentabilidade: 36,08%% a.a\nValor Minimo: "
               "R$34,49 cada cota");
        printf("\nDigite quantos [COTAS] deseja comprar: ");
        scanf("%f", &valor_investir);
        calc = (valor_investir * 34.49);
        cotas = (calc * 0.3608);
        total = calc + cotas;
        printf("Valor das cotas compradas: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
               "%.2f",
               total);
        break;
      case 2:
        printf("\nDescrição sobre SANB11\n");
        printf("Grau de Risco : Alto\nRentabilidade: 7,76%% a.a\nValor Minimo: "
               "R$30,22 cada cota");
        printf("\nDigite quantos [COTAS] deseja comprar: ");
        scanf("%f", &valor_investir);
        calc = (valor_investir * 30.22);
        cotas = (calc * 0.0776);
        total = calc + cotas;
        printf("Valor das cotas compradas: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
               "%.2f",
               total);
        break;
      case 3:
        printf("\nDescrição sobre PETR4\n");
        printf("Grau de Risco: Alto\nRentabilidade: 79,29%% a.a\nValor Minimo: "
               "R$34,25 cada cota ");
        printf("\nDigite quantos cotas deseja comprar: ");
        scanf("%f", &valor_investir);
        calc = (valor_investir * 34.25);
        cotas = (calc * 0.7929);
        total = calc + cotas;
        printf("Valor das cotas compras: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
               "%.2f",
               total);
        break;
      case 4:
        printf("\nDescrição sobre VALE3\n");
        printf("Grau de Risco: Alto\nRentabilidade: 0,46%% a.a\nValor Minimo: "
               "R$71,93 cada cota");
        printf("\nDigite quantos [COTAS] deseja comprar: ");
        scanf("%f", &valor_investir);
        calc = (valor_investir * 71.93);
        cotas = (calc * 0.0046);
        total = calc + cotas;
        printf("Valor das cotas compras: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
               "%.2f",
               total);
        break;
      case 0:
        main();
      }
    }

    // investimento em previdencia privada tudo tirado do Banco DIGITAL INTER
    if (investir == 4) {
      printf("\n1 - Previdencia privada\n");
      printf("0 - Sair\n");
      printf("Digite qual opcao deseja executar: ");
      scanf("%d", &escolher);
      if (escolher == 1) {
        printf("Grau de Risco: Alto\nRentabilidade de R$ 1.903,99 até R$ "
               "2.826,65: 7,5%% a.a\nR$ 2.826,66 até R$ 3.751,05: 15%% a.a\nR$ "
               "3.751,06 até R$ 4.664,68: 22,5%% a.a\nAcima de R$ 4.664,68: "
               "27,%%\nValor Minimo: R$35,00");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        if (valor_investir >= 1903.99 && valor_investir <= 2826.65) {
          calc = (valor_investir * 0.075);
          total = calc + valor_investir;
          printf("Valor investido : %.2f", (calc));
          printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
                 "%.2f",
                 total);
        }
        if (valor_investir >= 2826.66 && valor_investir <= 3751.05) {
          calc = (valor_investir * 0.15);
          total = calc + valor_investir;
          printf("Valor investido : %.2f", (calc));
          printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
                 "%.2f",
                 total);
        }
        if (valor_investir >= 3751.06 && valor_investir <= 4664.68) {
          calc = (valor_investir * 0.225);
          total = calc + valor_investir;
          printf("Valor investido: %.2f", (calc));
          printf("\nEsse seria o resultado do seu investimento durante 1 ano: "
                 "%.2f",
                 total);
          if (valor_investir >= 4664.68) {
            calc = (valor_investir * 0.275);
            total = calc + valor_investir;
            printf("Valor investido: %.2f", (calc));
            printf("\nEsse seria o resultado do seu investimento durante 1 "
                   "ano: %.2f",
                   total);
          }
        }

      } else {
        main();
      }
    }

    if (investir == 5) {
      printf("\n1 - Prefixado 2025\n");
      printf("2 - Tesouro Selic 2025\n");
      printf("3 - Tesouro IPCA 2026\n");
      printf("0 - Sair\n");
      printf("\nDigite qual lugar deseja aplicar seu dinheiro: ");
      scanf("%d", &escolher);

      switch (escolher) {
      case 1:
        printf("Descrição sobre Prefixado");
        printf("Grau de Risco: baixo\nRentabilidade : 11,92 a.a\nValor "
               "Minimo: R$31,33");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.1193) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
        break;
      case 2:
        printf("Descrição sobre Tesouro Selic 2025 ");
        printf("Grau de Risco: baixo\nRentabilidade : Taxa Selic + 0,039 "
               "a.a\nValor Minimo: R$123,38\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.1375) * valor_investir;
        cotas = calc + 0.0395;
        total = valor_investir + calc;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
        break;

      case 3:
        printf("Descricao sobre Tesouro IPCA 2026\n");
        printf(
            "Grau de Risco:baixo\nRentabilidade : Taxa Selic + 5,61 a.a\nValor "
            "Minimo: R$32,16\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.13) * valor_investir;
        cotas = calc + 0.0561;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
        break;
      case 0:
        main();
      }
    }
    // sistema de poupanca
    if (investir == 6) {
      printf("\n1 - Poupança\n");
      printf("0 - Sair\n");
      printf("Digite qual opcao deseja executar:");
      scanf("%d", &escolher);
      if (escolher == 1) {
        printf("Descricao sobre Poupanca\n");
        printf(
            "Grau de risco: baixo\nRentabilidade : 7,44 a.a\nValor Minimo: Não "
            "há valor minimo para esse investimento\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.0744) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      } else if (escolher == 0) {
        main();
      }
    }
    // sistema de investimento COE
    if (investir == 7) {
      printf("\n1 - COE\n");
      printf("0 - Sair\n");
      printf("Digite qual opcao deseja executar:");
      scanf("%d", &escolher);
      if (escolher == 1) {
        printf("Descricao sobre a COE");
        printf("\nGrau de risco: Medio\nRentabilidade: 20,0 a.a\nValor Minimo: "
               "R$5.000,00\n");
        printf("\nDigite quantos reais deseja investir: ");
        scanf("%f", &valor_investir);
        calc = (0.20) * valor_investir;
        total = calc + valor_investir;
        printf("\nIsso seria quantos reais renderia durante 1 ano: %.2f",
               (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f\n", total);
      } else if (escolher == 0) {
        main();
      }
    }
  }
  // Conta Corrente
  else if (escolha == 5) {
    int acao;
    printf("- CONTA CORRENTE -\n");
    printf("1 - Consultar CC\n");
    printf("2 - Depositar\n");
    printf("3 - Sacar\n");
    printf("0 - Sair\n");
    printf("\nDigite a opção desejada: ");
    scanf("%d", &acao);
    printf("\n");

    // Consultar CC
    if (acao == 1) {
      float valor_consulta;
      FILE *consulta = fopen("contacorrente.txt", "r");
      if (consulta == NULL) {
        printf("Conta corrente inexistente.\n");
        printf("Por gentileza, realizar um depósito.\n");
        main();
      } else {
        fscanf(consulta, "%f", &valor_consulta);
        printf("Sua conta corrente possui: %.2f reais\n", valor_consulta);
        main();
      }
      fclose(consulta);
    }
    // Depositar
    else if (acao == 2) {
      float deposito, valor_antigo, novo_valor;
      printf("Digite o valor a ser depositado: ");
      scanf("%f", &deposito);

      FILE *leitura = fopen("contacorrente.txt", "r");
      fscanf(leitura, "%f", &valor_antigo);
      fclose(leitura);

      novo_valor = valor_antigo + deposito;

      FILE *depositar = fopen("contacorrente.txt", "w");
      fprintf(depositar, "%f", novo_valor);
      fclose(depositar);

      printf("\nNovo saldo: %.2f\n", novo_valor);

      main();
    }
    // Sacar
    else if (acao == 3) {
      float saque, valor_antigo, novo_valor;
      printf("Digite o valor a ser sacado: ");
      scanf("%f", &saque);

      FILE *leitura = fopen("contacorrente.txt", "r");
      fscanf(leitura, "%f", &valor_antigo);
      fclose(leitura);

      novo_valor = valor_antigo - saque;

      FILE *sacar = fopen("contacorrente.txt", "w");
      fprintf(sacar, "%f", novo_valor);
      fclose(sacar);

      printf("\nNovo saldo: %.2f\n", novo_valor);

      main();
    }
    // Sair
    else if (acao == 0) {
      main();
    }
  }

  else {
    printf("Escolha inválida.\n");
    main();
  }
}