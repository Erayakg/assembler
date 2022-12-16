# assembler
Assembler
Programlama Dilleri (derleyiciler) giriş olarak yazılan bir programın kaynak kodunu alır ve ondan sonra 
kaynak kod program ne iş yapıyorsa, kendisi de aynı işi yapan programı yazar. Bu düşünce ile 8-bitlik 
bir El-Ceziri işlemcisinin olduğu varsayılsın. Bu işlemcinin RAM 8-bitlik 256 byte (hafıza) bulunmaktadır. 
Aynı zamanda üzerinde AX, BX, CX, DX şeklin dört tane 8-bitlik kayıtçı (register) bulunmaktadır. Bu 
işlemcinin komut kümesi aşağıdaki listede verilmiştir.
TOP OP1,OP2
CRP OP1,OP2
BOL OP1,OP2
CIK OP1,OP2
DS ETIKET
DSD ETIKET
DAL ETIKET
DK ETIKET
DB ETIKET
ATM OP1,OP2
VE OP1,OP2
VEY OP1,OP2
El-Ceziri işlemcisinin Assembleri yazılmış bir program bir metin (text) dosyasında olacaktır. 
Hazırlanacak program, bu dosya giriş olarak alacak ve bu Assembler ile yazılan program (dosyada 
olan program) ne iş yapıyorsa, hazırlanan program da aynı işi yapacaktır. Program bitiminde bütün 
registerların içeriğini ekrana yazacaktır ve eğer bellek kullanıldıysa, sadece belleğin o elemanı veya
elemanları ekrana yazılacaktır.
