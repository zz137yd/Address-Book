#pragma once
#define  _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <iostream>
#include <string>

#define MAX 100
#define NAME 15//姓名
#define GENDER 7//性别
#define ADDRESS 20//地址
#define WORK 20//职业
#define NUMBER 15//电话
#define SIZE 30//初始化时动态开辟的空间
#define ADD_SZ 10//增容时所用

typedef struct PeoInfo
{
	char name[NAME];
	char gender[GENDER];
	char address[ADDRESS];
	char work[WORK];
	char number[NUMBER];
	int age;
}PeoInfo;

typedef struct Contact
{
	PeoInfo* data;
	int sz;
	int capacity;
}Contact;


void LoadContact(Contact* ps);

void InitContact(Contact* ps);

void AddContact(Contact* ps);

void DelContact(Contact* ps);

int SpecifyDel(Contact* ps);

int BatchDel(Contact* pb);

void FindContact(Contact* ps);

void SortContact(Contact* ps);

void ModifyContact(const Contact* ps);

bool ShowContact(const Contact* ps);

void DestroyContact(Contact* ps);

void SaveContact(Contact* ps);