#include "main.c"


if (investir == 1) {
      printf("1 - LCI IPCA FINAL 3 ANOS\n");
      printf("2 - CDB LIQUIDEZ DIARIA\n");
      printf("3 - CDB VOITER\n");
      printf("4 - ENERGISA\n");
      printf("0 - Sair\n");

      printf("\nDigite qual lugar deseja aplicar seu dinheiro: ");
      scanf("%d", &escolher);
      if (escolher == 1) {
        printf("Descrição sobre LCI IPCA FINAL 3 ANOS\n");
        // IPCA é a inflação do mes tirei uma media durante 12 meses para
        // calcular
        printf("Grau de risco: Baixo\nRentabilidade: A partir de 4.41 + "
               "IPCA\nValor Minimo: R$50,00\nVencimento 23/10/2025\n");
        printf("\nDigite quantos reais deseja investir:");

        scanf("%d", &valor_investir);
        calc = (0.0714 + 0.0441) * valor_investir;
        total = calc + valor_investir;
        printf("Isso seria quantos reais renderia durante 1 ano: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 2) {
        printf("Descrição sobre CDB LIQUIDEZ DIARIA");
        printf(
            "\nGrau de risco: Muito baixo\nRentabilidade: A partir de 98.0 do "
            "CDI\nValor Minimo:R$100,00\nVencimento 08/10/2024\n");
        printf("\nDigite quantos reais deseja investir:");
        scanf("%d", &valor_investir);
        calc = (0.1167) * valor_investir;
        total = calc + valor_investir;
        printf("Isso seria quantos reais renderia durante 1 ano: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 3) {
        printf("Descrição sobre CDB VOITER");
        printf("\nGrau de risco: Médio\nRentabilidade: 14,25 a.a\nValor "
               "Minimo:R$1001,45\nVencimento 18/11/2024\n");
        printf("\nDigite quantos reais deseja investir:");
        scanf("%d", &valor_investir);
        calc = (0.1425) * valor_investir;
        total = calc + valor_investir;
        printf("Isso seria quantos reais renderia durante 1 ano: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 4) {
        printf("Descrição sobre ENERGISA");
        printf("\nGrau de risco: Alto\nRentabilidade: IPCA + 6.00 a.a\nValor "
               "Minimo: R$1008,45\nVencimento 15/04/2029");
        printf("\nDigite quantos reais deseja investir:");
        scanf("%d", &valor_investir);
        calc = (0.0714 + 0.06) * valor_investir;
        total = calc + valor_investir;
        printf("Isso seria quantos reais renderia durante 1 ano: %.2f", (calc));
        printf("\nEsse seria o resultado do seu investimento: %.2f", total);
      }
      if (escolher == 0) {
        return main();
      }
    }