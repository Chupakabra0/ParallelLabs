# Лабораторная работа №3

## Отчёт по лабораторной работе №3

по дисциплине "Параллельные и распредлённые вычисления"  
студента группы ПА-18-2  
Сафиюлина Александра Александровича

### Постановка задачи

* Напишите программу на языке программирования С, которая будет использовать два процесса;
* Организуйте передачу одномерного массива из нулевого процесса в первый;
* Вычислите сумму всех элементов массива и разошлите её всем процессам;
* Организуйте вывод результата в нулевом процессе;
* Использовать функции `MPI_Send` И `MPI_Recv`.

### Выполнение

Так как мы имеем дело с программой, которая работает с двумя 
процессами, то и дадим подробное описания двум функциям. Первая 
будет работать на нулевом процессе, вторая - на первом.

#### Функция нулевого процесса

Задача нулевого процесса: генерировать массив чисел типа `double`,
отправить его первому процессу, принять от него число типа `double`
и вывести оное. Код функции выглядит так:

```C
 void ZeroRankProcedure(int size) {
	double* array = AllocateRandomArray(size, ARRAY_RAND_MAX);
	MPI_Send(array, size, MPI_DOUBLE, SEND_TO_FIRST_PROCESS, FIRST_TASK, MPI_COMM_WORLD);

	double* sum = (double*)malloc(sizeof(double));
	MPI_Recv(sum, 1, MPI_DOUBLE, GET_FROM_FIRST_PROCESS, SECOND_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	fprintf(stdout, "0 process got value: sum = %lf", *sum);
	fprintf(stdout, "\n");
	fflush(stdout);

	free(sum);
	FreeArray(array);
}
```

Пожалуй, самым важным тут являются функции `MPI_Send` и 
`MPI_Recv`. 

Расскажем про первую функцию. Первый аргумент принимает 
указатель на данные, 
которые следует отправить. Количество этих данных определяет 
второй аргумент, третий - их тип. Четвёртый - номер процесса, в 
который нужно отправить данные, а пятый - идентификатор операции. 
Шестой аргумент указывает контекст, в котором производится 
операция отправки.

Расскажем про вторую функцию. По сути её аргументы аналогичны 
первой, кроме того, что она имеет седьмой аргумент, который 
сохраняет статус операции.

#### Фукнция первого процесса

Код ниже будет выполняться на первом процессе:

```C
void FirstRankProcedure(int size) {
	double* array = (double*)malloc(sizeof(double) * size);
	MPI_Recv(array, size, MPI_DOUBLE, GET_FROM_ZERO_PROCESS, FIRST_TASK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	fprintf(stdout, "1 process got value: array = ");
	PrintArray(stdout, array, array + size);
	fprintf(stdout, "\n");
	fflush(stdout);

	double* sum = (double*)malloc(sizeof(double));
	*sum = FindSum(array, array + size, Sum);

	MPI_Send(sum, 1, MPI_DOUBLE, SEND_TO_ZERO_PROCESS, SECOND_TASK, MPI_COMM_WORLD);

	free(sum);
	free(array);
}
```

Здесь используются аналогичные операции. Не будем 
останавливаться на них снова

### Примеры:

Примеры работы приложения на Windows 10 и Linux (Zorin OS):

![][windows-example]
![][linux-example]

[windows-example]: img/windows-example.png
[linux-example]: img/linux-example.png
