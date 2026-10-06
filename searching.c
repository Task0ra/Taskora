#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Provider{
int id;
char name[30];
char service[20];
float distance;
float rating;
float price;

srtuct Provider *next;
};
