// By Ronny Aprilio
// using Code::Blocks 13.12 Ubuntu version
// Needs : Grouping Auxiliary Ships and some bugs detected

#include <iostream>
#include <stdio.h>
#include <string.h>


using namespace std;

struct
{
    char type[20];
    char name[20];
    int lv;
}kanmusu;

struct
{
    char kanji[50];
    char translation[50];
}translation;

void simplify();
void parse();
char *parseKai(char data[50]);
char *translate(char input[50]);
int test_registered();


char temp[50];
char names[][70] = {"1st Floor", "2nd Floor", "3rd Floor", "4th Floor"};
char ship_type[][20] = {"戦艦", "正規空母", "航空戦艦", "高速戦艦", "航空巡洋艦", "重巡洋艦", "潜水艦", "軽空母", "駆逐艦", "軽巡洋艦", "Auxiliary", "水上機母艦", "重雷装巡洋艦"} ;
char ship_type_simplified[][20] = {"戦艦", "正規空母", "航戦", "高速戦艦", "航巡", "重巡", "潜水艦", "軽空母", "駆逐艦", "軽巡", "Auxiliary", "水母", "雷巡"};
//sensuikan dan kokunya masukin sensuikan, kosoku senkan pisahin dari senkan
char ship_type_romaji[][25] = {"Senkan", "Seiki-kubo", "Koku-Senkan", "Kosoku-Senkan", "Koku-Junyoukan", "Ju-Junyoukan", "Sensuikan", "Kei-Kubo", "Kuchikukan", "Kei-Junyoukan", "Auxiliary", "Suijou-Kibokan", "Juraisou-junyoukan"};
int counter = 0;

int main()
{
    //setlocale(LC_ALL, "ja_JP");
    simplify();
    parse();
    //test_segment();
    cout << "All Ships Data Count = " << counter << endl;
    cout << "Total Ships Unregistered = " << test_registered() << endl;

    return 0;
}

void parse()
{
    remove("output.txt");
    remove("registered.txt");
    int left = 1;
    FILE *output = fopen("output.txt", "w+");
    FILE *registered = fopen("registered.txt", "at");

    fprintf(output, "{| style='width: 100%; '\n");

    int slot_number = 1;
    int first_time = 1;

    for (int i = 0; i < sizeof(ship_type)/sizeof(ship_type[0]); i++)
    {

        if(left == 1)
        {
            fprintf(output, "{{FujiFleet-10 |\n");
            if(true)//(i+1) % 4 == 0)
            {
                fprintf(output, "| name= %s\n", names[i+1/4]);
            }
            else
            {
                fprintf(output, "| name= ");
            }
            fprintf(output, "| rname1= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
            slot_number = 1;
            left=0;
        }
        else
        {
            fprintf(output, "| rname2= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
            slot_number = 11;
            left=1;
        }

        FILE *s_data = fopen("simple_data.txt", "r");
        if(feof(s_data))
        {
            cout << "Parse : can't read file simple_data.txt." << endl;
        }
        else
        {
            while(!feof(s_data))
            {
                fscanf(s_data, "%s %s %d", &kanmusu.type, &kanmusu.name, &kanmusu.lv);
                if(strcmp(kanmusu.name, "Prinz")==0){strcpy(kanmusu.name, "Prinz Eugen改");}
                if(strcmp(kanmusu.name, "Graf")==0){strcpy(kanmusu.name, "Graf Zeppelin改");}

                if(strcmp(kanmusu.name,"榛名改二")==0 || strcmp(kanmusu.name,"Italia")==0 || strcmp(kanmusu.name,"Roma改")==0 || strcmp(kanmusu.name,"金剛改二")==0 || strcmp(kanmusu.name,"霧島改二")==0 || strcmp(kanmusu.name,"比叡改二")==0)
                {
                    strcpy(kanmusu.type, "高速戦艦");
                }

                if(strcmp(kanmusu.type,"潜水空母")==0){strcpy(kanmusu.type, "潜水艦");}


                if(strcmp(kanmusu.type, ship_type_simplified[i])==0)
                {
                    if(slot_number > 10 && left==0)
                    {
                        fprintf(output, "| rname2= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
                        slot_number = 11;
                        left=1;
                    }
                    if(slot_number > 20 && left==1)
                    {
                        fprintf(output, "{{FujiFleet-10 |\n");
                        fprintf(output, "| name= %s\n", names[i/2]);
                        fprintf(output, "| rname1= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
                        slot_number = 1;
                        left=0;
                    }
                    //| 1=  {{FslotJA |Yamato   |Kai    |129 }}
                    fprintf(output, "| %d = {{FslotJA |%s |%d }}\n", slot_number, parseKai(kanmusu.name), kanmusu.lv);
                    fprintf(registered, "%s %d\n", kanmusu.name, kanmusu.lv);
                    slot_number++;
                }
                else if(strcmp("Auxiliary", ship_type_simplified[i])==0)
                {
                    if(strcmp(kanmusu.type, "揚陸艦")==0 || strcmp(kanmusu.type, "工作艦")==0 || strcmp(kanmusu.type, "補給艦")==0 || strcmp(kanmusu.type, "練習巡洋艦")==0 || strcmp(kanmusu.type, "潜水母艦")==0)
                    {
                        if(slot_number > 10 && left==0)
                        {
                            fprintf(output, "| rname2= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
                            slot_number = 11;
                            left=1;
                        }
                        if(slot_number > 20 && left==1)
                        {
                            fprintf(output, "{{FujiFleet-10 |\n");
                            fprintf(output, "| name= %s\n", names[i/2]);
                            fprintf(output, "| rname1= %s (%s)\n", ship_type[i], ship_type_romaji[i]);
                            slot_number = 1;
                            left=0;
                        }
                        //| 1=  {{FslotJA |Yamato   |Kai    |129 }}
                        fprintf(output, "| %d = {{FslotJA |%s |%d }}\n", slot_number, parseKai(kanmusu.name), kanmusu.lv);
                        fprintf(registered, "%s %d\n", kanmusu.name, kanmusu.lv);
                        slot_number++;
                    }
                }
                if(first_time==1){counter++;}
            }
        }
        fclose(s_data);
        if(left==1){fprintf(output, "}}\n");}
        first_time = 0;
    }
    if(left == 0)
    {
        fprintf(output, "| rname2= Room 102 : 正規空母 (Seiki-kubo)\n");


        fprintf(output, "}}\n");
    }
    fprintf(output, "|}\n\n__NOTOC__");
    fclose(registered);
    fclose(output);
}

void simplify()
{
    remove("simple_data.txt");
    FILE *data = fopen("data.txt", "r");
    FILE *s_data = fopen("simple_data.txt", "at");
    if(feof(data) || feof(s_data))
    {
        cout << "Simplify : Can't read file data.txt." << endl;
    }
    else
    {
        char tmp[50];
        int iteration = 1;
        while(! feof(data))
        {
            fscanf(data, "%s", &tmp);
            if(iteration < 5 && iteration != 1)
            {
                if (strcmp(tmp,"Prinz")==0 || strcmp(tmp, "Graf")==0)
                {
                    strcpy(temp, strcat(tmp, " "));
                    fscanf(data, "%s", &tmp);
                    strcpy(tmp, strcat(temp,tmp));
                }
                fprintf(s_data, "%s\n", tmp);
                //cout << iteration << " : " << tmp << endl;
            }
            iteration++;

            if(iteration >= 16){iteration = 1;}
        }
    }
    fclose(data);
    fclose(s_data);
}


char *parseKai(char data[50])
{
    char out_put[40];
    char *pOut = out_put;
    char name[30];
    char remodel[10];

    strcpy(out_put, "");
    strcpy(name, "");
    strcpy(remodel, "");
    if(strcmp(data, "Prinz Eugen改")==0 || strcmp(data, "Graf Zeppelin改")==0 || strcmp(data, "Libeccio改")==0 || strcmp(data, "Верный")==0 )
    {
        strcat(data, " | ");
        pOut = data;
        return pOut;
    }
    else
    {
        for(int i=0; i < sizeof(data); i=i+3)
        {
            char kanji_char[4];
            strncpy(kanji_char, data+i, 3);

            //remodel
            if(strcmp(kanji_char,"改")==0)
            {
                strcat(remodel, "Kai");
                strncpy(kanji_char, data+i+3, 3);
                if(strcmp(kanji_char,"二")==0)
                {
                    strcat(remodel, " Ni");
                }
                break;
            }
            else if(strcmp(data, "呂500")==0)
            {
                strcpy(name, "Ro-500");
                break;
            }
            else if(strcmp(kanji_char, "伊")==0)
            {
                if(strcmp(data, "伊勢改")==0 || strcmp(data, "伊勢")==0){strcpy(name,"Ise");i=3;}//+3
                if(strcmp(data, "伊58改")==0 || strcmp(data, "伊58")==0){strcpy(name,"I-58");i=2;}//+3
                if(strcmp(data, "伊8改")==0 || strcmp(data, "伊8")==0){strcpy(name,"I-8");i=1;}
                if(strcmp(data, "伊19改")==0 || strcmp(data, "伊19")==0){strcpy(name,"I-19");i=2;}
                if(strcmp(data, "伊168改")==0 || strcmp(data, "伊168")==0){strcpy(name,"I-168");i=3;}
            }
            else
            {
                strcat(name, kanji_char);
            }
        }
    }

    strcat(out_put,translate(name));
    strcat(out_put," |");
    strcat(out_put,remodel);
    return pOut;
}

char *translate(char input[50])
{
    char *pInput = input;
    char temp[2][50];
    strcpy(temp[0], "");
    strcpy(temp[1], "");

    FILE *translation = fopen("translation.txt", "r");
    if (feof(translation))
    {
        cout << "Can't read file translation.txt\n";
    }
    else
    {
        while(!feof(translation) && strcmp(input, "あきつ丸") != 0)
        {
            fscanf(translation, "%s %s", &temp[0], &temp[1]); //temp[0] is the kanji, temp[1] for english translation
            if(strcmp(input, temp[0])==0)
            {
                strcpy(input, temp[1]);
                break;
            }
        }
    }
    fclose(translation);
    //exception
    if(strcmp(input, "あきつ丸") == 0){strcpy(input, "Akitsu Maru");}

    //end exception

    return pInput;
}

int test_registered()
{
    int counter_unreg = 0;//begin from 1, 4th, 7th, etc...
    char reg[2][50];
    char sdata[50];
    FILE *s_data = fopen("simple_data.txt", "r");
    int found, row;
    row = 1;
    cout << "Unregistered Ship :" << endl;
    while(!feof(s_data))
    {
        fscanf(s_data, "%s", &sdata);
        fscanf(s_data, "%s", &sdata);// twice scanf to get row 1
        found=0;
        FILE *registered = fopen("registered.txt", "r");
        while(!feof(registered) && row-1 % 3 == 0)
        {
            fscanf(registered, "%s %s", &reg[0], &reg[1]);
            if(strcmp(reg[0],sdata)==0){found=1;cout << "Found\n";}
        }
        fclose(registered);
        if(found==0){counter_unreg++; /*cout << row << " : " << parseKai(sdata) << endl;*/}
        row++;
    }
    fclose(s_data);
    return counter_unreg;
}
