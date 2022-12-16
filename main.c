#include <stdio.h>
#include <ctype.h>
int converterInt(char value[]){
    int i=0;
    int j=1;
    int newValue=0;
    while (value[i]!='\0'){
        i++;
        j=j*10;
    }
    j=j/10;
    int s;
    for (int k = 0; k <i ; k++) {
        s=(int)value[k];
        newValue+=(s-48)*j;
        j=j/10;
    }
    return  newValue;
}
int ramController(char token[]){
    /* Grammerdeki [int] değerini kontrol eden fonksiyondur.*/
    int i=0;
    char newtokens[10];
    int j=i+1;
    if(token[i]=='['){//ilk eleman [ ise başlar ve ] değeri gelene kadar bir başka diziye atar.Böylece sadece köşeli parantez içindeki değer okunur
        while (token[i]!=']'){
            newtokens[i]=token[j];
            i++;
            j++;
        }
        newtokens[j-2]='\0';
    }
    int a;
    a= converterInt(newtokens);
    return a;
}

int main() {
    FILE *fp;
    FILE *fp2;
    struct {
        char token[10];
    } Token[100];//dosyadaki kelimelerin struct yapısı oluşturulur
    char fileName[]="ornek.txt";
   // printf("dosya adini giriniz:");
    //gets(fileName);
    if ((fp = fopen(fileName, "r"))) {
        int j = 0;
        while (!feof(fp)) {
            fgetc(fp);
            j++;
        }
        fclose(fp);
        char array[j];
        fp2 = fopen(fileName, "r");
        for (int i = 0; i < j; ++i) {
            array[i] = getc(fp2);
        }
        fclose(fp2);
        int r = 0;
        int l = 0;
        for (int s = 0; s < j; s++) {
            //ayraçlara göre tokenlaştırma işlemi yapılır
            if (array[s] ==toascii(0x0A) || array[s] == toascii(0x2C) || array[s] == toascii(32) || array[s] == toascii(0x3A)) {
                Token[l].token[r] = '\0';
                s++;
                r = 0;
                l++;
            }
            Token[l].token[r++] = array[s];
        }
        int s;
        int AX=0;
        int BX;
        int CX;
        int DX;
        int RAM[300];
        RAM[0]=1;
        RAM[1]=2;
        int g=0;
        printf("\n <<  Tokens  >> \n");
        for (int b = 0; b <l+1; b++) {
            printf("<<Token>>");
            printf("%s", Token[b].token);
            printf("<<Token>>");
            printf("\n\n");
        }
        for (int d = 0; d <  l; d++) {
            switch (Token[d].token[g]) {
                case  'T':
                    d++;
                    if(Token[d].token[g]=='A') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                AX=AX+AX;
                                d++;
                                break;
                            case 'B':
                                AX=AX+BX;
                                d++;
                                break;
                            case 'C':
                                AX=AX+CX;
                                d++;
                                break;
                            case '[':
                                s=ramController(Token[d+1].token);
                                AX=AX+RAM[s];
                                d++;
                                break;
                            default:
                                AX=AX+ converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                else if(Token[d].token[g]=='B') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                BX=BX+AX;
                                d++;
                                break;
                            case 'B':
                                BX=BX+BX;
                                d++;
                                break;
                            case 'C':
                                BX=BX+CX;
                                d++;
                                break;
                            case '[':
                                s= ramController(Token[d+1].token);
                                BX=BX+RAM[s];
                                d++;
                                break;
                            default:
                                BX=BX+converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                else if(Token[d].token[g]=='C') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                CX=CX+AX;
                                d++;
                                break;
                            case 'B':
                                CX=CX+BX;
                                d++;
                                break;
                            case 'C':
                                CX=CX+CX;
                                d++;
                                break;
                            case '[':
                                s= ramController(Token[d+1].token);
                                CX=CX+RAM[s];
                                d++;
                                break;
                            default:
                                CX=CX+converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                    break;
                case 'C':
                    if(Token[d].token[g+1]=='R'){//CRP ve CIK hangi kelime  olduğu kontrol edilir
                        d++;
                        if(Token[d].token[g]=='A') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    AX=AX*AX;
                                    d++;
                                    break;
                                case 'B':
                                    AX=AX*BX;
                                    d++;
                                    break;
                                case 'C':
                                    AX=AX*CX;
                                    d++;
                                    break;
                                case '[':
                                    s=ramController(Token[d+1].token);
                                    AX=AX*RAM[s];
                                    d++;
                                    break;
                                default:
                                    AX=AX* converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        else if(Token[d].token[g]=='B') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    BX=BX*AX;
                                    d++;
                                    break;
                                case 'B':
                                    BX=BX*BX;
                                    d++;
                                    break;
                                case 'C':
                                    BX=BX*CX;
                                    d++;
                                    break;
                                case '[':
                                    s= ramController(Token[d+1].token);
                                    BX=BX*RAM[s];
                                    d++;
                                    break;
                                default:
                                    BX=BX*converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        else if(Token[d].token[g]=='C') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    CX=CX*AX;
                                    d++;
                                    break;
                                case 'B':
                                    CX=CX*BX;
                                    d++;
                                    break;
                                case 'C':
                                    CX=CX*CX;
                                    d++;
                                    break;
                                case '[':
                                    s= ramController(Token[d+1].token);
                                    CX=CX*RAM[s];
                                    d++;
                                    break;
                                default:
                                    CX=CX*converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        break;
                    } else{
                        d++;
                        if(Token[d].token[g]=='A') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    AX=AX-AX;
                                    d++;
                                    break;
                                case 'B':
                                    AX=AX-BX;
                                    d++;
                                    break;
                                case 'C':
                                    AX=AX-CX;
                                    d++;
                                    break;
                                case '[':
                                    s=ramController(Token[d+1].token);
                                    AX=AX-RAM[s];
                                    d++;
                                    break;
                                default:
                                    AX=AX-converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        else if(Token[d].token[g]=='B') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    BX=BX-AX;
                                    d++;
                                    break;
                                case 'B':
                                    BX=BX-BX;
                                    d++;
                                    break;
                                case 'C':
                                    BX=BX-CX;
                                    d++;
                                    break;
                                case '[':
                                    s= ramController(Token[d+1].token);
                                    BX=BX-RAM[s];
                                    d++;
                                    break;
                                default:
                                    BX=BX-converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        else if(Token[d].token[g]=='C') {
                            switch (Token[d+1].token[g]) {
                                case 'A':
                                    CX=CX-AX;
                                    d++;
                                    break;
                                case 'B':
                                    CX=CX-BX;
                                    d++;
                                    break;
                                case 'C':
                                    CX=CX-CX;
                                    d++;
                                    break;
                                case '[':
                                    s= ramController(Token[d+1].token);
                                    CX=CX-RAM[s];
                                    d++;
                                    break;
                                default:
                                    CX=CX-converterInt(Token[d+1].token);
                                    d++;
                                    break;
                            }
                        }
                        break;
                    }
                    break;
                case 'A':
                    d++;
                    if(Token[d].token[g]=='A'){
                        AX=converterInt(Token[d+1].token);
                        d++;
                    }
                    if(Token[d].token[g]=='B'){
                        BX=converterInt(Token[d+1].token);
                        d++;
                    }
                    if(Token[d].token[g]=='C'){
                        CX=converterInt(Token[d+1].token);
                        d++;
                    }
                    break;
                case 'B':
                    d++;
                    if(Token[d].token[g]=='A') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                DX=+AX % AX;
                                AX=AX/AX;
                                d++;
                                break;
                            case 'B':
                                DX+=AX % BX;
                                AX=AX/BX;
                                d++;
                                break;
                            case 'C':
                                DX=+AX%CX;
                                AX=AX/CX;
                                d++;
                                break;
                            case 'D':
                                DX=+AX%DX;
                                AX=AX/DX;
                                d++;
                                break;
                            case '[':
                                s=ramController(Token[d+1].token);
                                DX=+AX%s;
                                AX=AX/RAM[s];
                                d++;
                                break;
                            default:
                                DX=+AX%converterInt(Token[d+1].token);
                                AX=AX/converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                    else if(Token[d].token[g]=='B') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                DX=+BX%BX;
                                BX=BX/AX;
                                d++;
                                break;
                            case 'B':
                                DX=+BX%BX;
                                BX=BX/BX;
                                d++;
                                break;
                            case 'C':
                                DX=+BX%CX;
                                BX=BX/CX;
                                d++;
                                break;
                            case 'D':
                                DX=+BX%DX;
                                BX=BX/DX;
                                d++;
                                break;
                            case '[':
                                s= ramController(Token[d+1].token);
                                DX=+BX%s;
                                BX=BX/RAM[s];
                                d++;
                                break;
                            default:
                                DX=+BX% converterInt(Token[d+1].token);
                                BX=BX/converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                    else if(Token[d].token[g]=='C') {
                        switch (Token[d+1].token[g]) {
                            case 'A':
                                DX=+CX%AX;
                                CX=CX/AX;
                                d++;
                                break;
                            case 'B':
                                DX=+CX%BX;
                                CX=CX/BX;
                                d++;
                                break;
                            case 'C':
                                DX=+CX%CX;
                                CX=CX/CX;
                                d++;
                                break;
                            case '[':
                                s=ramController(Token[d+1].token);
                                DX=+CX%s;
                                CX=CX/RAM[s];
                                d++;
                                break;
                            default:
                                DX=+CX%converterInt(Token[d+1].token);;
                                CX=CX/converterInt(Token[d+1].token);
                                d++;
                                break;
                        }
                    }
                    break;
                case 'V':
                    if(Token[d].token[g+2]=='Y'){

                    } else{

                    }
                    break;
                case 'D':
                    if(Token[d].token[g+1]=='S')
                    {
                        if(Token[d].token[g+2]=='D'){

                        } else{

                        }
                    }
                    else if(Token[d].token[g+1]=='A')
                    {

                    }
                    else if(Token[d].token[g+1]=='K')
                    {

                    }
                    else if(Token[d].token[g+1]=='B')
                    {

                    }
                    break;
                default:
                    //printf("\nhatali");
                    break;
            }
        }
       // printf("\n\n\n");
        printf("\n\n\nAX:%d",AX);
        printf("\n\n\nBX:%d",BX);
        printf("\n\n\nCX:%d",CX);
        printf("\n\n\n\nDX:%d",DX);
    }
    else {
        printf("dosya bulunamadi");
    }

}