#include "FileHandler.h"
using namespace std;


void FileHandler::CreateStuList(const char* inputFilePath, const char* outputFilePath, int nCount)
{
	//读取txt文件
	FILE *inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		printf("无法读取学生数据， 请重启程序");
		return;
	}

	FILE* outputFile = fopen(outputFilePath, "wb");
	if (outputFile == NULL)
	{
		printf("无法写入学生数据, 请重启软件");
		fclose(inputFile);
		return;
	}

		//产生8位数的id
	for (int i = 1; i < nCount + 1; ++i)
	{
		student stu;
		int temp = i;
		//逐个构建字符串
		//并将字符串放到学生结构体的szId里
		for (int j = 0; j < SID_LEN; j++)
		{
			char digit = '0' + (temp % 10); //获取最后一位数字的字符表示
			(stu.m_szId)[SID_LEN - 1 -j] = digit; //将字符添加到字符串最前面
			temp /= 10; //去掉最后一位数字
		}
		(stu.m_szId)[SID_LEN] = '\0';
		fgets (stu.m_szName, sizeof(stu.m_szName), inputFile);  //姓名放到szName里
		size_t nLen = strlen(stu.m_szName);
		stu.m_szName[nLen - 2] = '\0';
		stu.m_szName[nLen - 1] = 0;
		//将结构体数据写入文件
		fwrite(&stu, sizeof(stu), 1, outputFile);
	}

	fclose(outputFile);
	fclose(inputFile);
	return;
}

void FileHandler::CreateCourseList(const char* inputFilePath, const char* outputFilePath, int nCount)
{
	//读取txt文件
	FILE* inputFile = fopen(inputFilePath, "rb");
	if (inputFile == NULL)
	{
		printf("无法读取课程数据，请重启程序");
		return;
	}

	FILE* outputFile = fopen(outputFilePath, "wb");
	if (outputFile == NULL)
	{
		printf("无法写入课程数据，请重启程序");
		fclose(inputFile);
		return;
	}

	//产生6位数的id
	for (int i = 1; i < nCount + 1; ++i)
	{
		course cou;
		int temp = i;
		//逐个构建字符串
		//并将字符串放到课程结构体的szStuId里
		for (int j = 0; j < CID_LEN; j++)
		{
			char digit = '0' + (temp % 10); //获取最后一位数字的字符表示
			(cou.m_szId)[CID_LEN - 1 - j] = digit; //将字符添加到字符串最前面
			temp /= 10; //去掉最后一位数字
		}
		(cou.m_szId)[CID_LEN] = '\0';
		fgets(cou.m_szName, sizeof(cou.m_szName), inputFile);  //姓名放到szName里
		size_t nLen = strlen(cou.m_szName);
		cou.m_szName[nLen - 2] = '\0';
		cou.m_szName[nLen - 1] = 0;
		//将结构体数据写入文件
		fwrite(&cou, sizeof(course), 1, outputFile);
	}

	fclose(outputFile);
	fclose(inputFile);
	return;
}

void FileHandler::CreateRecord(const char* stuFilePath, const char* courseFilePath, const char* outFilePath)
{
	int i = 0;
	//打开两个文件
	FILE* inputStuFile = fopen(stuFilePath, "rb");
	if (inputStuFile == NULL)
	{
		printf("无法读取学生文件生成选课记录，请重启程序");
		return;
	}

	FILE* inputCouFile = fopen(courseFilePath, "rb");
	if (inputCouFile == NULL)
	{
		printf("无法读取课程文件生成选课记录，请重启程序");
		fclose(inputStuFile);
		return;
	}

	FILE* outputFile = fopen(outFilePath, "wb");
	if (outputFile == NULL)
	{
		printf("无法写入选课记录");
		fclose(inputStuFile);
		fclose(inputCouFile);
		return;
	}
 
	srand(time(NULL));

	//从学生文件读取学生结构体
	student stu;
	record rd;
	course cou;
	int nReadCount;
	while (fread(&stu, sizeof(student), 1, inputStuFile) > 0)
	{
		//将学生结构体中的id拷贝到record结构体的szStuId
		memcpy(rd.m_szStuId, stu.m_szId, sizeof(rd.m_szStuId));
		for (i = 0; i < 10; ++i)
		{
			//读取course结构体
			nReadCount = fread(&cou, sizeof(course), 1, inputCouFile);
			if (nReadCount <= 0)   //此处可检查是否读到文件尾部
			{
				fseek(inputCouFile, 0, SEEK_SET); //如果读到尾部或者读取出错，
				i--;
				continue;
			}
			memcpy(rd.m_szCourseId, cou.m_szId,sizeof(rd.m_szCourseId)); //将courseId拷到record结构体的szCourseId
			rd.m_grade = rand() % 101;
			fwrite(&rd, sizeof(record), 1, outputFile);
		}
	}

	fclose(outputFile);
	fclose(inputCouFile);
	fclose(inputStuFile);

}
 		
 	
//int FileHandler::RandNum()
//{
//	int nRandNum;
//	srand(time(NULL));
//	nRandNum = rand() % 101;
//	return nRandNum;
//}
