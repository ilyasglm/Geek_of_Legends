#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

typedef struct
{
    char name[20]; // name of the players character.
    int hp;        // hp based on level 60 base hp + 10 hp / level.
    int level;     // level based on experience points, 3xp = level +1, 8xp = level +1,... Some fights might give more experience points.
    int xp;        // experience points.
    int ap;        // Attack points based on level, 15 attack points / level.
    int mp;        // Mana points, used to do quest and fights.
    int def;       // defense points based on level, 2 def points / level.
    int ult;       // Ultimate attack ult dmg = (player.ap * 2)+(player.ap / 2);
    int lucky;     // Lucky number designed by the player at the creation of the character.
} Personnage;
typedef struct
{
    char name[20]; // name of the Monster character.
    int hp;        // hp based on level 60 base hp + 10 hp / level.
    char grade;    // monsters grade from low to high : B,A,S,SSS.
    int ap;        // Attack points based on the grade;
    int def;       //Defense points based on the grade
} Monster;
int random_number(int min_num, int max_num);
void check_levelUp(Personnage *data);
void load_game(Personnage *data, char filename[20]);
void save_game(Personnage *data, char dataFile[20]);
int main()
{
    char playerName[20];
    int powerUp;
    char answer[20];
    char filename[20];
    char ext[5] = ".txt";
    char loadthis[150] = "/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/save/";
    char savethis[150] = "/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/save/";
    char newGame[150] = "/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/new.txt";
    char loadLucky[150] = "/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/lucky.txt";
    Personnage player = {"player", 60, 1, 0, 15, 3};
    Monster bgrade = {"Robin", 100, 'B', 10, 0};
    Monster agrade = {"Batman", 150, 'A', 25, 5};
    Monster sgrade = {"Superman", 250, 'S', 50, 10};
    Monster sssgrade = {"Cactus", 99999, 'X', 9999, 100};

    // Main screen .
    printf("Welcome to Geek of Legends.\n -New : new game\n -load : loads game\n");
    printf("Enter your choice : ");
    scanf("%s", answer);
    if (strcmp(answer, "load") == 0)
    {
        printf("Character name : ");
        scanf("%s", filename);
        strcat(filename, ext);
        strcat(loadthis, filename);
        load_game(&player, loadthis);
        printf("Loading game\n");
        strcat(savethis, filename);
    }
    else
    {
        load_game(&player, newGame);
        printf("Launching new game\n");
        printf("Enter player name : ");
        scanf("%s", playerName);
        printf("\nEnter your lucky number :");
        scanf("%d", &player.lucky);
        strcpy(player.name, playerName);
        strcat(savethis, playerName);
        strcat(savethis, ".txt");
    }

    int action;
    while (1)
    {
        printf("Available actions :\n - 1 = Quest  --search for a quest\n - 2 = Fight  --search for a fight\n - 3 = Meditate --meditate to gather xp and mp (35seconds / session).\n - 4 = Status --show player status.\n - 0 = Quit  --quit game.\n");
        printf("Action : ");
        scanf("%d", &action);

        switch (action)
        {

        case 1:
            if (player.mp > 0)
            {
                switch (random_number(1, 3))
                {
                case 1:
                    printf("You went on a low level quest. You'll be back in 5 seconds\n");
                    for (int i = 5; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(1);
                    }
                    printf("You have gained 3xp.\n");
                    player.xp += 3;
                    player.mp -= 1;
                    check_levelUp(&player);
                    break;
                case 2:
                    printf("You went on a medium level quest. You'll be back in 7 seconds\n");
                    for (int i = 7; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(1);
                    }
                    printf("You have gained 6xp.\n");
                    player.xp += 6;
                    player.mp -= 1;
                    check_levelUp(&player);
                    break;
                case 3:
                    printf("You went on a high level quest. You'll be back in 35 seconds\n");
                    for (int i = 10; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(1);
                    }
                    printf("You have gained 10xp.\n");
                    player.xp += 10;
                    player.mp -= 1;
                    check_levelUp(&player);
                    break;

                default:
                    break;
                }
                printf("Status : \nLevel : %d\nxp : %d\nhp : %d\nap : %d\nmp : %d\n", player.level, player.xp, player.hp, player.ap, player.mp);
            }
            else
            {
                printf("\nYou do not have enough mp.\n");
            }
            break;
        case 2:
            if (player.mp > 0)
            {
                int x = random_number(1, 100);
                if (x <= 50)
                {
                    printf("You found a B grade (%s) monster to fight. The fight is starting in 3 seconds get ready to RUMBLE !\n", bgrade.name);
                    for (int i = 3; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(1);
                    }
                    int temp1 = 0;
                    int loser = 0;
                    do
                    {
                        char fightAnswer[20];
                        printf("Your turn : \n  --attack : target - %d HP\n  --block : your hp - ((%d - %d)/2)\n  --run : 1/3 chance of escaping.\n  --ult : Ultimate skill, need to block 1 turn to get powered up .\n", player.ap, bgrade.ap, player.def);
                        scanf("%s", fightAnswer);
                        int temp = 0;

                        do
                        {
                            if (strcmp(fightAnswer, "attack") == 0)
                            {
                                temp = 1;
                                printf("%s attacks %s and does %d dmg.\n", player.name, bgrade.name, player.ap);
                                bgrade.hp -= player.ap;
                                sleep(2);
                                printf("It's %s's time to attack\n", bgrade.name);
                                printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, bgrade.ap);
                                printf("%s hp = %d, %s hp = %d.\n",bgrade.name, bgrade.hp, player.name,player.hp);
                                printf("\n\n\n");
                                player.hp -= bgrade.ap;
                            }
                            if (strcmp(fightAnswer, "ult") == 0)
                            {
                                if (powerUp == 1)
                                {
                                    powerUp = 0;
                                    player.ult = (player.ap * 2) + (player.ap / 2);
                                    printf("%s ults %s and does %d dmg.\n", player.name, bgrade.name, player.ult);
                                    bgrade.hp -= player.ult;
                                    sleep(2);
                                    printf("It's %s's time to attack\n", bgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n\n\n", bgrade.name, player.name, bgrade.ap);
                                    player.hp -= bgrade.ap;
                                }
                                else
                                {
                                    printf("You need to block a hit to get powered up !");
                                }
                            }

                            if (strcmp(fightAnswer, "block") == 0)
                            {
                                temp = 1;
                                printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                player.hp -= (player.def - bgrade.ap);
                                printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, (player.def - bgrade.ap));
                                powerUp = 1;
                                printf("%s's attack get powered up for 1 turn.\n\n\n", player.name);
                                sleep(2);
                            }
                            if (strcmp(fightAnswer, "run") == 0)
                            {
                                int run = random_number(1, 3);
                                if (run == 2)
                                {
                                    printf("You evaded successfully.\n\n\n");
                                    temp = 1;
                                    loser = 1;
                                }
                                else
                                {
                                    printf("You failed to run away.\n");
                                    printf("It's %s's time to attack\n", bgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n\n\n", bgrade.name, player.name, bgrade.ap);
                                    player.hp -= bgrade.ap;
                                }
                            }
                            printf("\nplayer HP : %d.\nMonster hp : %d.\n\n\n", player.hp, bgrade.hp);

                        } while (temp == 0);
                        if (player.hp < 0 || bgrade.hp < 0 || loser == 1)
                        {
                            system("clear");
                            temp1 = 1;
                            if (player.hp > 0 && bgrade.hp <= 0)
                            {
                                printf("You have killed %s and gained 4xp points. \n\n\n", bgrade.name);
                                player.xp += 4;
                            }
                            else if (player.hp <= 0 && bgrade.hp >= 0)
                            {
                                printf("%s has killed you, you lost 4xp points.\n\n\n", bgrade.name);
                                player.xp -= 4;
                            }
                            if (loser == 1)
                            {
                                printf("You evaded the combat. you didn't lose or gain anything.\nJust lost your dignity...\n\n\n");
                            }
                            player.mp -= 1;
                            check_levelUp(&player);
                            sleep(3);
                        }

                    } while (temp1 == 0);
                }

                if (x > 50 && x <= 80)
                {
                    printf("You found a A grade (%s) monster to fight. The fight is starting in 3 seconds get ready to RUMBLE !\n", agrade.name);
                    for (int i = 3; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(2);
                    }
                    int temp1 = 0;
                    int loser = 0;
                    do
                    {
                        char fightAnswer[20];
                        printf("Your turn : \n  --attack : target - %d HP\n  --block : your hp - ((%d - %d)/2)\n  --RUN : 1/3 chance of escaping.\n", player.ap, agrade.ap, player.def);
                        scanf("%s", fightAnswer);
                        int temp = 0;
                        do
                        {
                            if (strcmp(fightAnswer, "attack") == 0)
                            {
                                temp = 1;
                                printf("%s attacks %s and does %d dmg.\n\n\n", player.name, agrade.name, player.ap);
                                agrade.hp -= player.ap;
                                sleep(2);
                                printf("It's %s's time to attack\n", agrade.name);
                                printf("%s attacks %s and does %d dmg.\n\n\n", agrade.name, player.name, agrade.ap);
                                printf("%s hp = %d, %s hp = %d.\n",agrade.name, agrade.hp, player.name,player.hp);
                                printf("\n\n\n");
                                player.hp -= agrade.ap;
                            }
                            if (strcmp(fightAnswer, "ult") == 0)
                            {
                                temp = 1;
                                if (powerUp == 1)
                                {
                                    powerUp = 0;
                                    player.ult = (player.ap * 2) + (player.ap / 2);
                                    printf("%s ults %s and does %d dmg.\n\n\n", player.name, agrade.name, player.ult);
                                    agrade.hp -= player.ult;
                                    sleep(2);
                                    printf("It's %s's time to attack\n", agrade.name);
                                    printf("%s attacks %s and does %d dmg.\n\n\n", agrade.name, player.name, agrade.ap);
                                    player.hp -= agrade.ap;
                                }
                            }
                            if (strcmp(fightAnswer, "block") == 0)
                            {
                                temp = 1;
                                printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                player.hp -= (player.def - agrade.ap);
                                printf("%s attacks %s and does %d dmg.\n\n\n", agrade.name, player.name, (player.def - agrade.ap));
                                powerUp = 1;
                                printf("%s's attack get powered up for 1 turn.\n\n\n", player.name);
                            }
                            if (strcmp(fightAnswer, "run") == 0)
                            {
                                int run = random_number(1, 3);
                                temp = 1;
                                if (run == 2)
                                {
                                    printf("You evaded successfully.\n\n\n");
                                    loser = 1;
                                }
                                else
                                {
                                    printf("You failed to run away.\n\n");
                                    printf("It's %s's time to attack\n\n", agrade.name);
                                    printf("%s attacks %s and does %d dmg.\n\n\n", agrade.name, player.name, agrade.ap);
                                    player.hp -= agrade.ap;
                                }
                            }

                        } while (temp == 0);
                        if (player.hp < 0 || agrade.hp < 0 || loser == 1)
                        {
                            system("clear");
                            temp1 = 1;
                            if (player.hp > 0 && agrade.hp <= 0)
                            {
                                printf("You have killed %s and gained 4xp points. \n\n\n", agrade.name);
                                player.xp += 12;
                            }
                            else if (player.hp <= 0 && agrade.hp >= 0)
                            {
                                printf("%s has killed you, you lost 4xp points.\n\n\n", agrade.name);
                                player.xp -= 12;
                            }
                            if (loser == 1)
                            {
                                printf("You evaded the combat. you didn't lose or gain anything.\nJust lost your dignity...\n\n\n");
                            }
                            player.mp -= 1;
                            check_levelUp(&player);
                            sleep(3);
                        }
                    } while (temp1 == 0);
                }

                if (x > 80)
                {
                    int luckyNumber = random_number(1, 10000);
                    if (player.lucky == luckyNumber)
                    {
                        printf("\nYou are one hell of a lucky man my friend.\nCongratulations !!! you are blessed with the dev's luck !\nCheck Status ;)");
                        load_game(&player, loadLucky);
                    }
                    else
                    {
                        printf("You found an S grade (%s) monster to fight. The fight is starting in 3 seconds get ready to RUMBLE !\n", sgrade.name);
                        printf("%d",luckyNumber);
                        for (int i = 3; i > 0; i--)
                        {
                            printf("%d \n", i);
                            sleep(2);
                        }
                        int loser = 0;
                        int temp1 = 0;
                        do
                        {
                            char fightAnswer[20];
                            printf("Your turn : \n  --attack : target - %d HP\n  --block : your hp - ((%d - %d)/2)\n  --run : 1/3 chance of escaping.\n  --ult : ultimate blow, need to charge up. %d/1\n", player.ap, sgrade.ap, player.def, powerUp);
                            scanf("%s", fightAnswer);
                            int temp = 0;
                            do
                            {
                                if (strcmp(fightAnswer, "attack") == 0)
                                {
                                    temp = 1;
                                    printf("%s attacks %s and does %d dmg.\n", player.name, sgrade.name, player.ap);
                                    sgrade.hp -= player.ap;
                                    sleep(2);
                                    printf("It's %s's time to attack\n", sgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n\n\n", sgrade.name, player.name, sgrade.ap);
                                    printf("%s hp = %d, %s hp = %d.\n",sgrade.name, sgrade.hp, player.name,player.hp);
                                printf("\n\n\n");
                                    player.hp -= sgrade.ap;
                                }
                                if (strcmp(fightAnswer, "ult") == 0)
                                {
                                    temp = 1;
                                    if (powerUp == 1)
                                    {
                                        player.ult = (player.ap * 2) + (player.ap / 2);
                                        printf("%s ults %s and does %d dmg.\n", player.name, sgrade.name, player.ult);
                                        sgrade.hp -= player.ult;
                                        sleep(2);
                                        printf("It's %s's time to attack\n", sgrade.name);
                                        printf("%s attacks %s and does %d dmg.\n\n\n", sgrade.name, player.name, sgrade.ap);
                                        player.hp -= sgrade.ap;
                                        powerUp = 0;
                                    }
                                    else
                                    {
                                        printf("player needs to power up !\n\n\n");
                                    }
                                }
                                if (strcmp(fightAnswer, "block") == 0)
                                {
                                    temp = 1;
                                    printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                    player.hp -= (player.def - sgrade.ap);
                                    printf("%s attacks %s and does %d dmg.\n", sgrade.name, player.name, (player.def - sgrade.ap));
                                    powerUp = 1;
                                    printf("%s's attack get powered up for 1 turn.\n\n\n", player.name);
                                }
                                if (strcmp(fightAnswer, "RUN") == 0)
                                {
                                    int run = random_number(1, 3);
                                    if (run == 2)
                                    {
                                        printf("You evaded successfully.\n\n\n");
                                        temp = 1;
                                        loser = 1;
                                    }
                                    else
                                    {
                                        printf("You failed to run away.\n");
                                        printf("It's %s's time to attack\n", sgrade.name);
                                        printf("%s attacks %s and does %d dmg.\n\n\n", sgrade.name, player.name, sgrade.ap);
                                        player.hp -= sgrade.ap;
                                    }
                                }

                            } while (temp == 0);
                            if (player.hp < 0 || sgrade.hp < 0 || loser == 1)
                            {
                                system("clear");
                                if (player.hp > 0 && sgrade.hp <= 0)
                                {
                                    printf("You have killed %s and gained 4xp points. \n", sgrade.name);
                                    player.xp += 20;
                                }
                                else if (player.hp <= 0 && sgrade.hp > 0)
                                {
                                    printf("%s has killed you, you lost 4xp points.\n", sgrade.name);
                                    player.xp -= 20;
                                }
                                if (loser == 1)
                                {
                                    printf("You evaded the combat. you didn't lose or gain anything.\nJust lost your dignity...\n");
                                }
                                player.mp -= 1;
                                check_levelUp(&player);
                            }

                        } while (temp1 == 0);
                    }
                }

                printf("Status : \nLevel : %d\nxp : %d\nhp : %d\nap : %d\nmp : %d\n\n\n", player.level, player.xp, player.hp, player.ap, player.mp);
            }
            else
            {
                printf("\nYou do not have enough mp.\n\n");
            }
            break;
        case 3:
            printf("You have started to meditate far from worldly affairs...\n");
            for (int i = 0; i < 35; i++)
            {
                printf(" %d\n", i);
                sleep(1);
            }
            player.xp += 2;
            player.mp += 1;
            break;
        case 4:
            printf("Status : \nLevel : %d\nxp : %d\nhp : %d\nap : %d\nmp : %d\n", player.level, player.xp, player.hp, player.ap, player.mp);
            break;
        case 0:
            printf("Thanks for playing ! Saving Player in file %s.txt\n", player.name);
            save_game(&player, savethis);
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}

int random_number(int min_num, int max_num)
{
    srand(time(NULL));

    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    }
    else
    {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

void check_levelUp(Personnage *data)
{
    data->level = 1 + (data->xp / 5);
    data->hp = 60 + (data->level * 10);
    data->ap = (data->level * 15);
    data->def = (data->level * 2);
}

void load_game(Personnage *data, char dataFile[20])
{
    char str[20];
    int xp, mp,lucky;

    // open the file
    FILE *f = fopen(dataFile, "r");
    if ((f = fopen(dataFile, "r")) == NULL)
    {
        printf("\nSave file not found.\n");
        exit(1); // Program exits if file pointer returns NULL.
    }
    fscanf(f, "%s", str);
    fscanf(f, "%d", &xp);
    fscanf(f, "%d", &mp);
    fscanf(f, "%d", &lucky);
    fclose(f); // close file

    strcpy(data->name, str);
    data->xp = xp;
    data->mp = mp;
    data->lucky = lucky;
    check_levelUp(data);
}
void save_game(Personnage *data, char dataFile[20])
{
    // open the file
    FILE *f = fopen(dataFile, "w");
    fprintf(f, "%s\n", data->name);
    fprintf(f, "%d\n", data->xp);
    fprintf(f, "%d\n", data->mp);
    fprintf(f, "%d\n", data->lucky);
    fclose(f); // close file
}