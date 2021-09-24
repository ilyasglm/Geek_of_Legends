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
int check_levelUp(Personnage *data);
void load_game(Personnage *data, char filename[20]);
void save_game(Personnage *data);
int main()
{
    char playerName[20];
    int powerUp;
    char answer[20];
    char filename[20];
    char ext[5] = ".txt";
    char loadthis[150] = "/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/";
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
        printf("Filename : ");
        scanf("%s", filename);
        strcat(filename, ext);
        strcat(loadthis, filename);
        load_game(&player, loadthis);
        printf("Loading game\n");
    }
    else
    {
        printf("Launching new game\n");
        printf("Enter player name : ");
        scanf("%s",playerName);
        printf("\nEnter your lucky number :");
        scanf("%d",&player.lucky);
        load_game(&player, newGame);
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
                    int loser = 0;
                    while (player.hp > 0 || bgrade.hp > 0 || loser == 0)
                    {
                        char fightAnswer[20];
                        printf("Your turn : \n  --attack : target - %d HP\n  --block : your hp - ((%d - %d)/2)\n  --RUN : 1/3 chance of escaping.\n", player.ap, bgrade.ap, player.def);
                        scanf("%s", fightAnswer);
                        int temp = 0;
                        do
                        {
                            if (strcmp(fightAnswer, "attack") == 0)
                            {
                                temp = 1;
                                if (powerUp == 0)
                                {
                                    printf("%s ults %s and does %d dmg.\n", player.name, bgrade.name, player.ult);
                                    bgrade.hp -= player.ap;
                                    sleep(1);
                                    printf("It's %s's time to attack\n", bgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, bgrade.ap);
                                    player.hp -= bgrade.ap;
                                }
                                if (powerUp == 1)
                                {
                                    player.ult = (player.ap * 2) + (player.ap / 2);
                                    printf("%s attacks %s and does %d dmg.\n", player.name, bgrade.name, player.ap);
                                    bgrade.hp -= player.ult;
                                    sleep(1);
                                    printf("It's %s's time to attack\n", bgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, bgrade.ap);
                                    player.hp -= bgrade.ap;
                                    powerUp = 0;
                                }
                            }
                            if (strcmp(fightAnswer, "block"))
                            {
                                temp = 1;
                                printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                player.hp -= (player.def - bgrade.ap);
                                printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, (player.def - bgrade.ap));
                                powerUp = 1;
                                printf("%s's attack get powered up for 1 turn.\n", player.name);
                            }
                            if (strcmp(fightAnswer, "RUN"))
                            {
                                int run = random_number(1, 3);
                                if (run == 2)
                                {
                                    printf("You evaded successfully.\n");
                                    temp = 1;
                                    loser = 1;
                                }
                                else
                                {
                                    printf("You failed to run away.\n");
                                    printf("It's %s's time to attack\n", bgrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", bgrade.name, player.name, bgrade.ap);
                                    player.hp -= bgrade.ap;
                                }
                            }

                        } while (temp == 0);
                    }
                    if (player.hp >= 0 && bgrade.hp <= 0)
                    {
                        printf("You have killed %s and gained 4xp points. \n", bgrade.name);
                        player.xp += 4;
                    }
                    else if (player.hp <= 0 && bgrade.hp >= 0)
                    {
                        printf("%s has killed you, you lost 4xp points.\n", bgrade.name);
                        player.xp -= 4;
                    }
                    if (loser == 1)
                    {
                        printf("You evaded the combat. you didn't lose or gain anything.\nJust lost your dignity...\n");
                    }
                    player.mp -= 1;
                    check_levelUp(&player);
                }

                if (x > 50 && x <= 80)
                {
                    printf("You found a A grade (%s) monster to fight. The fight is starting in 3 seconds get ready to RUMBLE !\n", agrade.name);
                    for (int i = 3; i > 0; i--)
                    {
                        printf("%d \n", i);
                        sleep(1);
                    }
                    int loser = 0;
                    while (player.hp > 0 || agrade.hp > 0 || loser == 0)
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
                                if (powerUp == 0)
                                {
                                    printf("%s ults %s and does %d dmg.\n", player.name, agrade.name, player.ult);
                                    agrade.hp -= player.ap;
                                    sleep(1);
                                    printf("It's %s's time to attack\n", agrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", agrade.name, player.name, agrade.ap);
                                    player.hp -= agrade.ap;
                                }
                                if (powerUp == 1)
                                {
                                    player.ult = (player.ap * 2) + (player.ap / 2);
                                    printf("%s attacks %s and does %d dmg.\n", player.name, agrade.name, player.ap);
                                    agrade.hp -= player.ult;
                                    sleep(1);
                                    printf("It's %s's time to attack\n", agrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", agrade.name, player.name, agrade.ap);
                                    player.hp -= agrade.ap;
                                    powerUp = 0;
                                }
                            }
                            if (strcmp(fightAnswer, "block"))
                            {
                                temp = 1;
                                printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                player.hp -= (player.def - agrade.ap);
                                printf("%s attacks %s and does %d dmg.\n", agrade.name, player.name, (player.def - agrade.ap));
                                powerUp = 1;
                                printf("%s's attack get powered up for 1 turn.\n", player.name);
                            }
                            if (strcmp(fightAnswer, "RUN"))
                            {
                                int run = random_number(1, 3);
                                if (run == 2)
                                {
                                    printf("You evaded successfully.\n");
                                    temp = 1;
                                    loser = 1;
                                }
                                else
                                {
                                    printf("You failed to run away.\n");
                                    printf("It's %s's time to attack\n", agrade.name);
                                    printf("%s attacks %s and does %d dmg.\n", agrade.name, player.name, agrade.ap);
                                    player.hp -= agrade.ap;
                                }
                            }

                        } while (temp == 0);
                    }
                    if (player.hp >= 0 && agrade.hp <= 0)
                    {
                        printf("You have killed %s and gained 4xp points. \n", agrade.name);
                        player.xp += 12;
                    }
                    else if (player.hp <= 0 && agrade.hp >= 0)
                    {
                        printf("%s has killed you, you lost 4xp points.\n", agrade.name);
                        player.xp -= 12;
                    }
                    if (loser == 1)
                    {
                        printf("You evaded the combat. you didn't lose or gain anything.\nJust lost your dignity...\n");
                    }
                    player.mp -= 1;
                    check_levelUp(&player);
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
                        for (int i = 3; i > 0; i--)
                        {
                            printf("%d \n", i);
                            sleep(1);
                        }
                        int loser = 0;
                        while (player.hp > 0 || sgrade.hp > 0 || loser == 0)
                        {
                            char fightAnswer[20];
                            printf("Your turn : \n  --attack : target - %d HP\n  --block : your hp - ((%d - %d)/2)\n  --RUN : 1/3 chance of escaping.\n", player.ap, sgrade.ap, player.def);
                            scanf("%s", fightAnswer);
                            int temp = 0;
                            do
                            {
                                if (strcmp(fightAnswer, "attack") == 0)
                                {
                                    temp = 1;
                                    if (powerUp == 0)
                                    {
                                        printf("%s ults %s and does %d dmg.\n", player.name, sgrade.name, player.ult);
                                        sgrade.hp -= player.ap;
                                        sleep(1);
                                        printf("It's %s's time to attack\n", sgrade.name);
                                        printf("%s attacks %s and does %d dmg.\n", sgrade.name, player.name, sgrade.ap);
                                        player.hp -= sgrade.ap;
                                    }
                                    if (powerUp == 1)
                                    {
                                        player.ult = (player.ap * 2) + (player.ap / 2);
                                        printf("%s attacks %s and does %d dmg.\n", player.name, sgrade.name, player.ap);
                                        sgrade.hp -= player.ult;
                                        sleep(1);
                                        printf("It's %s's time to attack\n", sgrade.name);
                                        printf("%s attacks %s and does %d dmg.\n", sgrade.name, player.name, sgrade.ap);
                                        player.hp -= sgrade.ap;
                                        powerUp = 0;
                                    }
                                }
                                if (strcmp(fightAnswer, "block"))
                                {
                                    temp = 1;
                                    printf("%s holds his shield high in order to block the incomming attack\n", player.name);
                                    player.hp -= (player.def - sgrade.ap);
                                    printf("%s attacks %s and does %d dmg.\n", sgrade.name, player.name, (player.def - sgrade.ap));
                                    powerUp = 1;
                                    printf("%s's attack get powered up for 1 turn.\n", player.name);
                                }
                                if (strcmp(fightAnswer, "RUN"))
                                {
                                    int run = random_number(1, 3);
                                    if (run == 2)
                                    {
                                        printf("You evaded successfully.\n");
                                        temp = 1;
                                        loser = 1;
                                    }
                                    else
                                    {
                                        printf("You failed to run away.\n");
                                        printf("It's %s's time to attack\n", sgrade.name);
                                        printf("%s attacks %s and does %d dmg.\n", sgrade.name, player.name, sgrade.ap);
                                        player.hp -= sgrade.ap;
                                    }
                                }

                            } while (temp == 0);
                        }
                        if (player.hp >= 0 && sgrade.hp <= 0)
                        {
                            printf("You have killed %s and gained 4xp points. \n", sgrade.name);
                            player.xp += 20;
                        }
                        else if (player.hp <= 0 && sgrade.hp >= 0)
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
                }

                printf("Status : \nLevel : %d\nxp : %d\nhp : %d\nap : %d\nmp : %d\n", player.level, player.xp, player.hp, player.ap, player.mp);
            }
            else
            {
                printf("\nYou do not have enough mp.\n");
            }
            break;
        case 3:
            printf("You have started to meditate far from worldly affairs...\n");
            for (int i = 0; i < 35; i++)
            {
                printf(" %d\n", i);
            }
            player.xp += 2;
            player.mp += 1;
            break;
        case 4:
            printf("Status : \nLevel : %d\nxp : %d\nhp : %d\nap : %d\nmp : %d\n", player.level, player.xp, player.hp, player.ap, player.mp);
            break;
        case 0:
            printf("Thanks for playing ! Saving Player\n");
            save_game(&player);
            return 0;
            break;
        default:
            break;
        }
    }
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

int check_levelUp(Personnage *data)
{
    data->level = 1 + (data->xp / 5);
    data->hp = 60 + (data->level * 10);
    data->ap = (data->level * 15);
    data->def = (data->level * 2);
}

void load_game(Personnage *data, char filename[20])
{
    char str[20];
    int xp, mp;

    // open the file
    FILE *f = fopen(filename, "r");
    if ((f = fopen("/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/autosave.txt", "r")) == NULL)
    {
        printf("\nSave file not found.\n");
        exit(1); // Program exits if file pointer returns NULL.
    }
    fscanf(f, "%s", str);
    fscanf(f, "%d", &xp);
    fscanf(f, "%d", &mp);
    fclose(f); // close file

    strcpy(data->name, str);
    data->xp = xp;
    data->mp = mp;
    check_levelUp(data);
}
void save_game(Personnage *data)
{
    // open the file
    FILE *f = fopen("/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/autosave.txt", "w");
    if ((f = fopen("/Users/ilyasglm/coding18/C_projects/Geek_of_Legends/autosave.txt", "w")) == NULL)
    {
        printf("\nSave file not found.\n");
        exit(1); // Program exits if file pointer returns NULL.
    }
    fprintf(f, "%s\n", data->name);
    fprintf(f, "%d\n", data->xp);
    fprintf(f, "%d\n", data->mp);
    fclose(f); // close file
}