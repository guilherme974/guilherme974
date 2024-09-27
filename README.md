typedef struct item{
    char produto;
    float preco;
    int quantidade;
    } item;

    int main() {

        item carrinho[16];
        float total = 0.0;
        int N = 0;

        File *fp;
        fp = fopen("lista.txt", "r");
        if (fp == NULL) {
        printf("ERRO: não foi possível abrir o arquivo");
        exit(1);
           }

           while(fscanf(fp, "%s %d %f", carrinho[N].Produto, &carrinho[n].preco) != EOF)
    }
