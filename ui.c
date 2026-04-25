#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/*ANSI COLOR CODES*/
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"
#define C_BRED    "\033[91m"
#define C_BGREEN  "\033[92m"
#define C_BYELLOW "\033[93m"
#define C_BBLUE   "\033[94m"
#define C_BWHITE  "\033[97m"
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_DEFAULT "\033[0m"
#define C_RED     "\033[31m"
#define C_DIM     "\033[2m"
#define YL        C_BYELLOW C_BOLD
#define RD        C_RED     C_BOLD
#define RS        C_RESET
 
#define NAME_LEN    20
#define HEAL_AMOUNT 30
#define MAX_BREEDS   4
 
/*BREED TABLE for How to Play display)*/
typedef struct {
    char name[16];
    char talim_name[20];
    char talim_desc[64];
    int  base_hp;
    int  base_sugod;
} Breed;
 
static Breed breed_list[MAX_BREEDS] = {
    { "Banaba",  "Tukaa",        "150% sugod damage",               100, 25 },
    { "Joloano", "Kamros",       "120% dmg, ignores Ilag",          120, 22 },
    { "Kelso",   "Takot",        "Enemy sugod halved for 1 turn",    90, 20 },
    { "Sweater", "Pakpak Pakak", "2 hits, 65% acc, 80% dmg each",   85, 23 },
};
 
/*MISC*/
void clear_screen(void) { printf("\033[2J\033[H"); }
 
void print_line(void) {
    printf(C_DIM "     ──────────────────────────────────────────────\n" C_RESET);
}
 
void press_enter(void) {
    printf(C_DIM "\n     [ Press ENTER to continue... ]" C_RESET);
    int c; while ((c = getchar()) != '\n' && c != EOF);
}
 
/*TITLE SCREEN*/
void show_title(void) {
    clear_screen();
    printf("\n\n");
 
    printf("  "
        YL"██████"RD"╗ "RS  YL" █████"RD"╗  "RS
        YL"██████"RD"╗  "RS  YL"██████"RD"╗ "RS
        YL"███"RD"╗"YL"   ██"RD"╗ "RS  YL"██████"RD"╗ "RS "\n");
 
    printf("  "
        YL"██"RD"╔═══╝  "RS  YL"██"RD"╔══"YL"██"RD"╗"RS
        YL"██"RD"╔══"YL"██"RD"╗"RS  YL"██"RD"╔═══"YL"██"RD"╗"RS
        YL"████"RD"╗  "YL"██"RD"║"RS  YL"██"RD"╔════╝ "RS "\n");
 
    printf("  "
        RD"╚"YL"█████"RD"╗  "RS  YL"███████"RD"║"RS
        YL"██████"RD"╔╝"RS  YL"██"RD"║   "YL"██"RD"║"RS
        YL"██"RD"╔"YL"██"RD"╗ "YL"██"RD"║"RS  YL"██"RD"║  "YL"███"RD"╗"RS "\n");
 
    printf("  "
        " "RD"╚═══"YL"██"RD"╗ "RS  YL"██"RD"╔══"YL"██"RD"║"RS
        YL"██"RD"╔══"YL"██"RD"╗"RS  YL"██"RD"║   "YL"██"RD"║"RS
        YL"██"RD"║╚"YL"██"RD"╗"YL"██"RD"║"RS  YL"██"RD"║   "YL"██"RD"║"RS "\n");
 
    printf("  "
        YL"██████"RD"╔╝ "RS  YL"██"RD"║  "YL"██"RD"║"RS
        YL"██████"RD"╔╝"RS  RD"╚"YL"██████"RD"╔╝"RS
        YL"██"RD"║ ╚"YL"████"RD"║"RS  RD"╚"YL"██████"RD"╔╝"RS "\n");
 
    printf(C_DEFAULT);
    printf("  "RD"╚═════╝  ╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝"RS"\n");
 
    printf(C_RED C_BOLD "\n                ─────  SA TERMINAL  ─────\n" C_RESET);
    printf(C_DIM "          A Filipino Cockfighting Terminal Game\n\n" C_RESET);
    print_line();
    printf(C_CYAN "                  [1]" C_RESET " Host Game\n");
    printf(C_CYAN "                  [2]" C_RESET " Join Game\n");
    printf(C_CYAN "                  [3]" C_RESET " How to Play\n");
    printf(C_CYAN "                  [4]" C_RESET " Quit\n");
    print_line();
    printf(C_BYELLOW "                  > " C_RESET);
}
 
/*HOW TO PLAY*/
void show_how_to_play(void) {
    clear_screen();
    printf("\n");
    print_line();
    printf(C_BYELLOW C_BOLD "                  HOW TO PLAY\n" C_RESET);
    print_line();
    printf("\n");
 
    printf(C_BYELLOW "     MOVES:\n" C_RESET);
    printf("       " C_BGREEN "[1] SUGOD" C_RESET "  — Basic attack. Dmg = your Sugod stat\n");
    printf("       " C_BBLUE  "[2] TALIM" C_RESET "  — Special move, unique per breed\n");
    printf("       " C_CYAN   "[3] ILAG " C_RESET "  — Defend: halve incoming dmg next turn\n");
    printf("       " C_YELLOW "[4] BAWI " C_RESET "  — Heal +%d HP (cannot exceed max)\n\n", HEAL_AMOUNT);
 
    printf(C_BYELLOW "     BREEDS & TALIM SPECIALS:\n" C_RESET);
    for (int i = 0; i < MAX_BREEDS; i++) {
        Breed *b = &breed_list[i];
        printf("       " C_BWHITE "%-10s" C_RESET
               " HP:" C_BGREEN "%-4d" C_RESET
               " Sugod:" C_BYELLOW "%-3d" C_RESET
               "  " C_BBLUE "%-14s" C_RESET "— %s\n",
               b->name, b->base_hp, b->base_sugod,
               b->talim_name, b->talim_desc);
    }
 
    printf("\n");
    printf(C_BYELLOW "     RULES:\n" C_RESET);
    printf("       • Ilag blocks 50%% damage the NEXT turn only\n");
    printf("       • Kelso's Takot debuff lasts 1 turn\n");
    printf("       • Fight ends when a player reaches 0 HP\n");
    printf("       • Coin flip decides who attacks first\n\n");
 
    printf(C_BYELLOW "     NETWORK:\n" C_RESET);
    printf("       • One player hosts, the other joins\n");
    printf("       • Each player picks their own breed\n");
    printf("       • Moves are sent over the network\n\n");
 
    press_enter();
}
 
/*NAME ENTRY*/
void show_name_entry(char *my_name, int is_host) {
    clear_screen();
    printf("\n");
    print_line();
 
    if (is_host)
        printf(C_BYELLOW C_BOLD "                  YOU ARE: HOST\n" C_RESET);
    else
        printf(C_BBLUE   C_BOLD "                  YOU ARE: CLIENT\n" C_RESET);
 
    print_line();
    printf("\n");
 
    printf("     Enter your name: ");
    char buf[64];
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0)
            snprintf(my_name, NAME_LEN, is_host ? "Host" : "Client");
        else
            strncpy(my_name, buf, NAME_LEN - 1);
        my_name[NAME_LEN - 1] = '\0';
    }
 
    printf("\n");
    print_line();
    printf("     Welcome, %s%s" C_RESET "!\n",
           is_host ? C_BYELLOW : C_BBLUE, my_name);
    printf(C_DIM "     Waiting for opponent...\n" C_RESET);
 
    print_line();
    press_enter();
}
 
/*MAIN*/
int main(void) {
    char my_name[NAME_LEN] = {0};
 
    int running = 1;
    while (running) {
        show_title();
 
        char buf[8];
        if (!fgets(buf, sizeof(buf), stdin)) break;
        switch (atoi(buf)) {
            case 1:
                /* Host Game */
                show_name_entry(my_name, 1);
                break;
            case 2:
                /* Join Game */
                show_name_entry(my_name, 0);
                break;
            case 3:
                show_how_to_play();
                break;
            case 4:
                running = 0;
                break;
            default:
                break;
        }
    }
 
    clear_screen();
    printf("\n     " C_BGREEN "Paalam! Hanggang sa susunod na sabong!\n\n" C_RESET);
    return 0;
}
 