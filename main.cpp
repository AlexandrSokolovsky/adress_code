/*
main.cpp
Соколовский А.В.
23.10.2022

основной файл с main()
программа, которая выделяет 32КБ памяти, заполняет полосатым кодом - 52525, записывает в файл в бинарном виде

закомментирована функция для считывания с файла read_from_file
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int write_to_file(const char [],unsigned short int &);
unsigned short int &read_from_file(const char[], unsigned short int &);
int shift(int, unsigned short int *);

int main()
{
	int N = 5;
	unsigned short int *ptr = (unsigned short int*)calloc(32 * 1024 / sizeof(unsigned short int), sizeof(unsigned short int));

	int size = 32 * 1024 / sizeof(unsigned short int);



	for (int i = 0; i < size; i++)
	{
		*(ptr + i) = i;
	}
	write_to_file("file_1.bin", *ptr);

	for (int i = 0; i < size; i++)
	{
		*(ptr + i) = (size - i);
	}
	write_to_file("file_2.bin", *ptr);




	unsigned short int *ptr_1 = (unsigned short int*)calloc(32 * 1024 / sizeof(unsigned short int), sizeof(unsigned short int));

	*ptr = read_from_file("file_1.bin", *ptr);
	*ptr_1 = read_from_file("file_2.bin", *ptr_1);


	for (int i = 0; i < size-1; i++)
	{
		unsigned short int temp = *(ptr + i);
		*(ptr + i) = *(ptr + i + 1);
		*(ptr + i + 1) = temp;

		temp = *(ptr_1 + i);
		*(ptr_1 + i) = *(ptr_1 + i + 1);
		*(ptr_1 + i + 1) = temp;
	}


	shift(N, ptr);
	shift(N, ptr_1);


	free(ptr);
	free(ptr_1);

	return 0;
}

/*
запись в файл в бинарном виде

const char name[] - имя файла, в который будем записывать данные
unsigned short int &ptr - массив, заполенный адрессным кодом
*/
int write_to_file(const char name[], unsigned short int &ptr)
{

	FILE *write_ptr;

	write_ptr = fopen(name, "wb+");
	fwrite(&ptr, 32 * 1024, 1, write_ptr);

	fclose(write_ptr);

	return 0;
}


/*
считвание с файла в бинарном виде

const char name[] - имя файла, с которого будем считывать данные
unsigned short int &ptr - массив, который заполеним адрессным кодом из файла
*/
unsigned short int &read_from_file(const char name[], unsigned short int &ptr)
{
	int size = 0;

	FILE *rptr;


	rptr = fopen(name, "rb+");
	if (rptr)
	{
		fseek(rptr, 0, SEEK_END);
		size = ftell(rptr);
		fseek(rptr, 0, SEEK_SET);

		fread(&ptr, size, 1, rptr);

		fclose(rptr);
	}

	return ptr;
}



/*
циклический сдвиг массива

int N - число, на которое нужно сдвинуть. Если число - положительное, сдвиг вправо
unsigned short int *ptr - указатель на массив, который необходимо сдвинуть
*/
int shift(int N, unsigned short int *ptr)
{
	int size = 32 * 1024 / sizeof(unsigned short int);

	unsigned short int *temp = (unsigned short int*)calloc(size, sizeof(unsigned short int));

	for (int i = 0; i < size; i++)
	{
		temp[(i + N) % size] = ptr[i];
	}

	for (int i = 0; i < size; i++)
	{
		ptr[i] = temp[i];
	}

	free(temp);

	return 0;
}