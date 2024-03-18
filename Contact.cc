#include "Contact.h"
using namespace std;

static int check_capacity(Contact* ps)
{
	if (ps->sz == ps->capacity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(ps->data, (ADD_SZ + ps->capacity) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += ADD_SZ;
			cout << "增容成功" << endl;
			return 1;
		}
		else
		{
			perror("check_capacity:");
			return 0;
		}
	}
	else return 1;
}

void LoadContact(Contact* ps)
{
	FILE* pf = fopen("E:/Computer.txt", "r");
	if (pf == NULL)
	{
		perror("LoadContact::fopen");
		return;
	}
	PeoInfo ptr = { 0 };
	while (fread(&ptr, sizeof(PeoInfo), 1, pf))
	{
		check_capacity(ps);
		ps->data[ps->sz] = ptr;
		++ps->sz;
	}
	fclose(pf);
	pf = NULL;
}

void InitContact(Contact* ps)
{
	assert(ps);
	ps->data = (PeoInfo*)malloc(SIZE * sizeof(PeoInfo));
	if (ps->data == NULL)
	{
		perror("InitContact()");
		return;
	}
	ps->sz = 0;
	ps->capacity = SIZE;
}

void DestroyContact(Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
	ps->capacity = 0;
	ps->sz = 0;
}

void SaveContact(Contact* ps)
{
	FILE* pb = fopen("E:/Address Book.txt", "w");
	FILE* pc = fopen("E:/Computer.txt", "wb");
	if (pb == NULL || pc == NULL)
	{
		perror("SaveContact");
		return;
	}
	int i = 0;
	for (i = 0; i < ps->sz; i++)
	{
		fprintf(pb, "姓名：%s  性别：%s  地址：%s  工作：%s  电话：%s  年龄：%d\n", ps->data[i].name, ps->data[i].gender, ps->data[i].address, ps->data[i].work, ps->data[i].number, ps->data[i].age);
		fwrite(&(ps->data[i]), sizeof(PeoInfo), 1, pc);
	}
	fclose(pb);
	fclose(pc);
	pb = NULL;
	pc = NULL;
}

void AddContact(struct Contact* ps)
{
	assert(ps);
	if (0 == check_capacity(ps)) return;

	int flag = 1, ret = 0;
	string s;
	while (flag)
	{
		cout << "请输入要添加的名字:> ";
		while ((ret = getchar()) != '\n' && ret != EOF);
		getline(cin, s);
		int i = 0;
		while (i < ps->sz)
		{
			if (ps->data[i].name == s)
			{
				cout << "已有重复联系人, 请重新输入" << endl;
				break;
			}
			++i;
		}
		if (i == ps->sz) flag = 0;
	}
	strcpy(ps->data[ps->sz].name, s.c_str());

	cout << "请输入要添加的性别:> ";
	cin >> ps->data[ps->sz].gender;
	while ((ret = getchar()) != '\n' && ret != EOF);

	cout << "请输入要添加的地址:> ";
	getline(cin, s);
	strcpy(ps->data[ps->sz].address, s.c_str());

	cout << "请输入要添加的职业:> ";
	getline(cin, s);
	strcpy(ps->data[ps->sz].work, s.c_str());

	cout << "请输入要添加的电话号码:> ";
	std::cin >> ps->data[ps->sz].number;

	cout << "请输入要添加的年龄:> ";
	std::cin >> ps->data[ps->sz].age;

	++ps->sz;
	cout << "已成功添加第" << ps->sz << "个联系人" << endl;
}

int SpecifyDel(Contact* ps)
{
	assert(ps);
	int j = 0;
	int i = 0;
	int m = 0;
	cout << "请输入要删除的代号: >";
	while (cin >> m)
	{
		if (m < 1 || m > ps->sz)
		{
			cout << "此代号不存在，请重新输入！" << endl;
			continue;
		}
		else break;
	}
	m -= 1;
	FILE* bin = fopen("E://recycle bin.txt", "a");
	if (bin == NULL)
	{
		perror("ZDDel::fopen");
		cout << "文件创建失败，请重新进行删除" << endl;
		return 1;
	}
	fprintf(bin, "姓名：%s  性别：%s  地址：%s  工作：%s  电话：%s  年龄：%d\n", ps->data[m].name, ps->data[m].gender, ps->data[m].address, ps->data[m].work, ps->data[m].number, ps->data[m].age);
	fclose(bin);
	bin = NULL;
	for (j = m; j < ps->sz - 1; j++)
	{
		ps->data[j] = ps->data[j + 1];
	}
	--ps->sz;
	cout << "成功删除指定联系人" << endl;
	return 0;
}

void InsertSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp > a[end])
			{
				a[end + 1] = a[end];
				--end;
			}
			else break;
		}
		a[end + 1] = tmp;
	}
}

int BatchDel(Contact* pb)
{
	assert(pb);
	int num[30] = { 0 };
	int n = 0;
	int m = 1;
	int size = 0;
	cout << "请输入要删除的序列号: " << endl;
	cout << "选择好后, 输入 666 即可进行批量删除" << endl;
	while (m && cin >> n)
	{
		if (n == 666) break;

		num[size] = n;
		if (size < 30) ++size;

		if (size == 30)
		{
			cout << "最多选择30个, 是否开始删除? 0、是   1、否" << endl;
			cin >> m;
			if(m) cout << "您可以继续选择, 但只会删除前30个" << endl;
		}
	}
	InsertSort(num, size);
	FILE* bin = fopen("E://recycle bin.txt", "a");
	if (bin == NULL)
	{
		perror("ZDDel::fopen");
		cout << "文件创建失败，请重新进行删除" << endl;
		return 1;
	}
	int x = pb->sz, y = 0, z = 0, ret = 0;
	while (x >= 1)
	{
		while (x != num[z]) --x;

		y = x - 1;
		while ((y + 1) == num[z] && z < size)
		{
			fprintf(bin, "姓名：%s  性别：%s  地址：%s  工作：%s  电话：%s  年龄：%d\n", pb->data[y].name, pb->data[y].gender, pb->data[y].address, pb->data[y].work, pb->data[y].number, pb->data[y].age);
			y--;
			z++;
		}
		y += 1;
		ret = x - y;
		for (int i = y; i < pb->sz - ret; i++)
		{
			pb->data[i] = pb->data[i + ret];
		}
		pb->sz = pb->sz - ret;
		x = y;
	}
	fclose(bin);
	bin = NULL;
	return 0;
}

void DelContact(Contact* ps)
{
	assert(ps);
	int n = 0, s = 1, b = 1, i = 0, num = 0;
	char ret[20] = { '\0' };
	cout << "进行删除前请仔细看好每个联系人的代号" << endl;
	if (!ShowContact(ps)) return;
	cout << "请选择删除模式: 1、指定删除  2、批量删除" << endl;
	while (cin >> n)
	{
		if (n == 1)
		{
			while (s)
			{
				s = SpecifyDel(ps);
				if (s != 0) ++num;
				if (3 == num)
				{
					cout << "程序自身已出现错误3次, 强制退出, 请重新开始" << endl;
					s = 0;
					num = 0;
				}
			}
			break;
		}
		else if (n == 2)
		{
			while (b)
			{
				b = BatchDel(ps);
				if (b != 0) ++num;
				if (3 == num)
				{
					cout << "程序自身已出现错误3次, 强制退出, 请重新开始" << endl;
					b = 0;
					num = 0;
				}
			}
			break;
		}
		else
		{
			cout << "请重新输入" << endl;
			continue;
		}
	}
}

static int FindByName(const string str, const struct Contact* pf)
{
	int i = 0;
	for (i = 0; i < pf->sz; i++)
	{
		if (pf->data[i].name == str) return i;
	}
	return -1;
}

void FindContact(const struct Contact* ps)
{
	assert(ps);
	string s;
	cout << "请输入要查找的名字: >";
	getline(cin, s);
	int ret = FindByName(s, ps);
	if (ret == -1) cout << "要查找的人不存在" << endl;
	else
	{
		printf("%-15s\t%-10s\t%-22s\t%-22s\t%-16s\t%-5s\n", "姓名", "性别", "地址", "职业", "号码", "年龄");
		printf("%-15s\t%-10s\t%-22s\t%-22s\t%-16s\t%-5d\n", ps->data[ret].name,
			ps->data[ret].gender,
			ps->data[ret].address,
			ps->data[ret].work,
			ps->data[ret].number,
			ps->data[ret].age);
	}
}

void ModifyContact(const struct Contact* ps)
{
	cout << "请输入要修改的人的名字:>";
	int ch = 0;
	string s;
	while ((ch = getchar()) != '\n' && ch != EOF);
	getline(cin, s);
	int ret = FindByName(s, ps);
	if (ret == -1) cout << "要修改的人不存在" << endl;
	else
	{
		cout << "请输入修改后的名字:>";
		getline(cin, s);
		strcpy(ps->data[ret].name, s.c_str());
		cout << "请输入要修改的性别:>";
		cin >> ps->data[ret].gender;
		while ((ch = getchar()) != '\n' && ch != EOF);
		cout << "请输入要修改的地址:>";
		getline(cin, s);
		strcpy(ps->data[ret].address, s.c_str());
		cout << "请输入要修改的职业:>";
		getline(cin, s);
		strcpy(ps->data[ret].work, s.c_str());
		cout << "请输入要修改的电话号码:>";
		cin >> ps->data[ret].number;
		cout << "请输入要修改的年龄:>";
		cin >> ps->data[ret].age;
		cout << "修改成功" << endl;
	}
}

bool ShowContact(const struct Contact* ps)
{
	cout << endl;
	if (0 == ps->sz)
	{
		cout << "暂无联系人" << endl;
		return false;
	}
	int i = 0;
	printf("   %-15s\t%-10s\t%-22s\t%-22s\t%-16s\t%-5s\n", "姓名", "性别", "地址", "职业", "号码", "年龄");
	for (i = 0; i < ps->sz; i++)
	{
		printf("%d. %-15s\t%-10s\t%-22s\t%-22s\t%-16s\t%-5d\n", (i + 1),
			ps->data[i].name,
			ps->data[i].gender,
			ps->data[i].address,
			ps->data[i].work,
			ps->data[i].number,
			ps->data[i].age);
	}
	return true;
}

int CmpByName(const void* q1, const void* q2)
{
	return strcmp(((PeoInfo*)q1)->name, ((PeoInfo*)q2)->name);
}

void SortContact(const struct Contact* ps)
{
	qsort(ps->data, ps->sz, sizeof(struct PeoInfo), CmpByName);
}