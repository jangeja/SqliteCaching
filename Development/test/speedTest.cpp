#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        //printf, ("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    //printf("\n");
    return 0;
}


int insertTestEntries(sqlite3 *db) {
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    // Create 100,000 entries with uniquie id and rotating colors 
    int random;
    string color;

    for (int i = 0; i < 100000; i++) {
        random = rand() % 10;
        /* Create SQL statement */
        switch(random) {
            case 0:
                color = "BLUE";
                break;
            case 1:
                color = "GREEN";
                break;
            case 2:
                color = "RED";
                break;
            case 3:
                color = "YELLOW";
                break;
            case 4:
                color = "PURPLE";
                break;
            case 5:
                color = "BLACK";
                break;
            case 6:
                color = "WHITE";
                break;
            case 7:
                color = "BROWN";
                break;
            case 8:
                color = "ORANGE";
                break;
            case 9:
                color = "GRAY";
                break;
            default:
                break;
        }
         
        temp = "INSERT INTO COLORS(ID, COLOR) VALUES (" + to_string(i) + ",'" + color + "');";
        cout << temp << endl;
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());
        
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }

        else {
            fprintf(stdout, "Table created successfully\n");
        }
        delete [] sql;
    }

    return 0;
}

double getDuration(double t1, double t2) {
    double duration = t2 - t1;
    return duration/CLOCKS_PER_SEC;
}

/* 
 *************** TEST CASES ***************
 * */
void test1(sqlite3 * db) {
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 1 *******" << endl;
    cout << "Running the same SELECT * statement for one tuple 500,000 times." << endl;
    
    for (int i = 0; i < 500000; i++) {
        temp = "SELECT * FROM COLORS WHERE id = 7;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl << endl;
}


void test2(sqlite3 * db) {
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 2 *******" << endl;
    cout << "Running the same SELECT COLOR statement for one data item 500,000 times." << endl;
    
    for (int i = 0; i < 500000; i++) {
        temp = "SELECT COLOR FROM COLORS WHERE id = 7;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl << endl;
}

void test3(sqlite3 * db) {
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 3 *******" << endl;
    cout << "Running the SELECT * for each 100,000 unique key in the databse." << endl;
    
    for (int i = 0; i < 100000; i++) {
        temp = "SELECT * FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl << endl;
}

void test4(sqlite3 * db) {
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 4 *******" << endl;
    cout << "Running the SELECT COLOR for each 100,000 unique key in the databse." << endl;
    
    for (int i = 0; i < 100000; i++) {
        temp = "SELECT COLOR FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl << endl;
}

/*
 * Main
 * */
int main(int argc, char **argv) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char * sql;
    
    /* Open Database */
    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    else {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Run tests in sequence
    cout << "Running tests..." << endl << endl;
    test1(db);
    test2(db);
    test3(db);
    test4(db);

    cout << "End." << endl;    
    return 0;
}
