#include "Contact.h"

void menu()
{
	printf("\n");
	printf("*************************************\n");
	printf("*******   1. 增加   2. 删除   *******\n");
	printf("*******   3. 查找   4. 修改   *******\n");
	printf("*******   5. 展示   6. 排序   *******\n");
	printf("*******   7. 保存   0. 退出   *******\n");
	printf("*************************************\n");
	printf("\n");
}

enum Options
{
	Exit,
	Add,
	Del,
	Find,
	Modify,
	Show,
	Sort,
	Save,
};

int main()
{
	int input = 0;
	Contact book;
	InitContact(&book);
	LoadContact(&book);
	do
	{
		menu();
		while (true)
		{
			printf("请输入1到8之间的数字: ");
			if (scanf("%d", &input) != 1)
			{
				printf("请重新输入整数\n");
				while (getchar() != '\n');
			}
			else if (input < 0 || input > 8)
			{
				printf("错误, 请输入1到8之间的数字\n");
				while (getchar() != '\n');
			}
			else break;
		}
		switch (input)
		{
		case Add:
			AddContact(&book);
			break;
		case Del:
			DelContact(&book);
			break;
		case Find:
			//FindContact(&book);
			break;
		case Modify:
			ModifyContact(&book);
			break;
		case Show:
			ShowContact(&book);
			break;
		case Sort:
			//SortContact(&book);
			break;
		case Save:
			SaveContact(&book);
			break;
		case Exit:
			SaveContact(&book);
			DestroyContact(&book);
			std::cout << "退出通讯录" << std::endl;
			break;
		}
	} while (input);
	return 0;
}
