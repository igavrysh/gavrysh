//
//  IDPStructures.h
//  SuperCProject
//
//  Created by Ievgen on 4/11/16.
//  Copyright © 2016 Ievgen Gavrysh. All rights reserved.
//

/*
Задачи:
1. Создать структуру, данных, хранящую в себе расположенные в случайном порядке 6 bool, 1X float, 1X int, 1X long long, 3X short, 1X double, 1 Xуказатель на строку.
Требования:
- создать тестовый метод, который бы с помощью offsetof выводил расположение каждого из элементов;
- создать тестовый метод, который бы выводил размер всей структуры;
- перекомпоновать структуру так, чтобы она занимала наименьшее количество места;
- поместить bool значения в битовое поле и создать union;
2. Создать метод для вывода битов числа в консоль.
*/

#ifndef IDPStructures_h
#define IDPStructures_h
#include <stdbool.h>

typedef struct IDPStartUp IDPStartUp;

struct IDPStartUp {
    bool _isAngelInvestments;
    char *_startUpName;
    bool _isVentureFondInverstments;
    float _revenueEarned;
    bool _isGovernmetnInverstments;
    double _profitEarned;
    bool _isMultipleFounders;
    long long _usersCovered;
    bool _isFounderMajorStakeholder;
    int _suppliersNum;
    bool _isCreditBorrowed;
    short _employeesNum;
};

typedef struct IDPStartUpCompressed IDPStartUpCompressed;

struct IDPStartUpCompressed {
    char *_startUpName;
    //
    float _revenueEarned;
    int _suppliersNum;
    //
    double _profitEarned;
    //
    long long _usersCovered;
    //
    short _employeesNum;
    bool _isAngelInvestments;
    bool _isVentureFondInverstments;
    bool _isGovernmetnInverstments;
    bool _isMultipleFounders;
    bool _isFounderMajorStakeholder;
    bool _isCreditBorrowed;
    
};

#endif /* IDPStructures_h */

