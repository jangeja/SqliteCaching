#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

static int callback(void *file, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        fprintf ((FILE *) file, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    fprintf((FILE *) file, "\n");
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
    FILE * t_out = fopen("Log/Test_1.txt", "w"); 
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
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 1 complete." << endl << endl;
    fclose(t_out);
}


void test2(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_2.txt", "w");
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
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 2 complete." << endl << endl;
    fclose(t_out);
}

void test3(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_3.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 3 *******" << endl;
    cout << "Running the SELECT * for each 500,000 unique key in the database." << endl;
    
    for (int i = 0; i < 500000; i++) {
        temp = "SELECT * FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 3 complete." << endl << endl;
    fclose(t_out);
}

void test4(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_4.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 4 *******" << endl;
    cout << "Running the SELECT COLOR for each 500,000 unique key in the database." << endl;
    
    for (int i = 0; i < 500000; i++) {
        temp = "SELECT COLOR FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 4 complete." << endl << endl;
    fclose(t_out);
}

void test5(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_5.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 5 *******" << endl;
    cout << "SELECT * id 1 alternated with incrementing id 500,000 times (i.e. 1, 2, 1, 3, 1, 4...)." << endl;
    
    for (int i = 0; i < 250000; i++) {
        temp = "SELECT * FROM COLORS WHERE id = 1;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
        
        temp = "SELECT * FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 5 complete." << endl << endl;
    fclose(t_out);
}

void test6(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_6.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 6 *******" << endl;
    cout << "SELECT COUNT(*) GROUP BY COLOR 100 times." << endl;
    
    for (int i = 0; i < 100; i++) {
        temp = "SELECT COUNT(*) FROM COLORS GROUP BY COLOR;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
        
    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 6 complete." << endl << endl;
    fclose(t_out);
}

void test7(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_7.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 7 *******" << endl;
    cout << "SELECT * id 1-99 and increment next by one (i.e. 1...99, 100, 1...99, 101...) 500,000 queries." << endl;
    
    for (int i = 0; i < 5000; i++) {
        for (int j = 1; j < 100; j++) {
            temp = "SELECT * FROM COLORS WHERE ID = " + to_string(j) + ";";
            sql = new char[temp.length() + 1];
            strcpy(sql, temp.c_str());

            /* Execute SQL statement */
            rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
            
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
            }
            delete [] sql;
            
        }
        
        temp = "SELECT * FROM COLORS WHERE ID = " + to_string(i + 100) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

        
    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 7 complete." << endl << endl;
    fclose(t_out);
}

void test8(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_8.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 8 *******" << endl;
    cout << "SELECT id 1-3 and increment next by one (i.e. 1...3, 4, 1...3, 5...) 500,000 queries." << endl;
    for (int i = 0; i < 125000; i++) {
        for (int j = 1; j < 4; j++) {
            temp = "SELECT * FROM COLORS WHERE ID = " + to_string(j) + ";";
            sql = new char[temp.length() + 1];
            strcpy(sql, temp.c_str());

            /* Execute SQL statement */
            rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
            
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
            }
            delete [] sql;
            
        }
        
        temp = "SELECT * FROM COLORS WHERE ID = " + to_string(i + 4) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
    }

    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 8 complete." << endl << endl;
    fclose(t_out);
}

void test9(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_9.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 9 *******" << endl;
    cout << "SELECT SUM of Likability 100 times." << endl;
    
    for (int i = 0; i < 100; i++) {
        temp = "SELECT SUM(COLORS.LIKABILITY) FROM COLORS GROUP BY COLOR;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
        
    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 9 complete." << endl << endl;
    fclose(t_out);
}

void test10(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_10.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 10 *******" << endl;
    cout << "SELECT AVG of Likability 100 times." << endl;
    
    for (int i = 0; i < 100; i++) {
        temp = "SELECT AVG(COLORS.LIKABILITY) FROM COLORS GROUP BY COLOR;";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
        
    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 10 complete." << endl << endl;
    fclose(t_out);
}

void test11(sqlite3 * db) {
    FILE * t_out = fopen("Log/Test_11.txt", "w");
    char *zErrMsg = 0;
    int rc;
    char * sql;
    string temp;
    double start, end;
    start = clock();
    
    cout << "******* TEST 11 *******" << endl;
    cout << "SELECT each unique id and UPDATE each Likability field." << endl;
    
    for (int i = 0; i < 250000; i++) {
        temp = "SELECT * FROM COLORS WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;
        
        int random = rand() % 10;
        temp = "UPDATE COLORS SET LIKABILITY = " + to_string(random) + " WHERE id = " + to_string(i) + ";";
        sql = new char[temp.length() + 1];
        strcpy(sql, temp.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, t_out, &zErrMsg);
        
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        delete [] sql;

    }
    end = clock();
    cout << "-- Execution Time: " + to_string(getDuration(start, end)) << endl;
    cout << "Test 11 complete." << endl << endl;
    fclose(t_out);
}
/*
 * Main
 * */
int main(int argc, char **argv) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char * sql;
  
    // Remove old log files
    cout << "Removing old log files..." << endl;
    remove("Log/Test_1.txt");
    remove("Log/Test_2.txt");
    remove("Log/Test_3.txt");
    remove("Log/Test_4.txt");
    remove("Log/Test_5.txt");
    remove("Log/Test_6.txt");
    remove("Log/Test_7.txt");
    remove("Log/Test_8.txt");
    remove("Log/Test_9.txt");
    remove("Log/Test_10.txt");
    remove("Log/Test_11.txt");

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
    test5(db);
    test6(db);
    test7(db);
    test8(db);
    test9(db);
    test10(db);
    test11(db);

    cout << "End." << endl;   
    return 0;
}
