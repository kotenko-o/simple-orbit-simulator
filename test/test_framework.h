/**
 * @file test_framework.h
 * @brief Minimaler Unit-Test-Framework für C.
 *
 * Dieses Framework stellt eine einfache Infrastruktur zum Ausführen von
 * Unit-Tests bereit. Es enthält Makros zum Starten von Tests, zur
 * Bewertung von Asserts sowie zur formatierten Ausgabe der
 * Testergebnisse in der Konsole.
 *
 * Hauptfunktionen:
 *  - Ausführen der Testfunktionen
 *  - Zählen erfolgreicher und fehlgeschlagener Asserts pro Test
 *  - Formatierte Statusausgabe
 *  - Optionale Nutzung des Standard-assert() von C
 *  - Unterdrückung von Konsolenausgaben während eines Tests
 *
 * @author Oleksandr K.
 * @date 13.03.2026
 * @version 2.1
 */

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

/* 
 * Wenn folgende Zeile auskommentiert ist, wird "smart" 
 * Assert benutzt. Sonst die standard C assert()
 */
// #define USE_STANDARD_ASSERT

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef USE_STANDARD_ASSERT
    #include <assert.h>
#endif

/* ------------------------------
 * Definition of variables
 * ------------------------------ */
extern int passed_asserts;
extern int failed_asserts;

extern int passed_tests;
extern int failed_tests;

extern int test_number;
extern int is_test_failed; // 0 - OK, 1 - Failed, 2 - Aborted

/* ------------------------------
 * Output formatting defines
 * ------------------------------ */
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define BG_COLOR_YELLOW "\033[43m"
#define COLOR_RED "\033[31m"
#define BG_COLOR_RED "\033[41m"
#define COLOR_RESET "\033[0m"

#define S_RUN "[ RUN    ]"
#define S_OK "[     OK ]"
#define S_FAILED "[  FAILED ]"
#define S_ERROR  "[ ABORTED ]"

#define SEPARATION_LINE fprintf(stderr, COLOR_RESET "--------------------------------------------------\n")
#define SEPARATION_LINE_FAT fprintf(stderr, COLOR_RESET "==================================================\n")

#define STATUS_MSG(color, status, name) fprintf(stderr, color status "[%d] " name " - %.1f%%"                           \
                                        COLOR_RESET "\n", test_number, success_rate(passed_asserts, failed_asserts))
#define MSG(color, msg, ...) fprintf(stderr, "   -> " color msg COLOR_RESET "\n", ##__VA_ARGS__)

#define TEST_HEADER do {SEPARATION_LINE_FAT; printf("          Testing %s\n", __FILE__);} while(0)

/* ------------------------------
 * Functions and macro
 * ------------------------------ */

/*
 * @brief Hilfsfunktion zur Berechnung der Erfolgsrate
 * 
 * @param[in] int passed    Anzahl der erfolgreichen Versuche
 * @param[in] int failed    Anzahl der gescheiterten Versuche
 */
static inline float success_rate(int passed, int failed) {
    int total = passed + failed;
    return total > 0 ? 100.0f * passed / total : 0.0f;
}

/**
 * @brief Makro, das die Ausgabe einer Funktion nach /dev/null umleitet
 *
 * Notwendig, um beim Testing der Funktionen mit Console-Ausgabe
 * kein "Müll" in Logs zu haben.
 * @note Funktioniert nur bei Linux-Systemen
 */

#ifdef _WIN32
  #include <io.h>
  #include <fcntl.h>
  #define DEV_NULL "nul"
  #define DUP _dup
  #define DUP2 _dup2
  #define FILENO _fileno
  #define CLOSE _close
  #define OPEN _open
  #define O_WRONLY _O_WRONLY
#else
  #include <unistd.h>
  #include <fcntl.h>
  #define DEV_NULL "/dev/null"
  #define DUP dup
  #define DUP2 dup2
  #define FILENO fileno
  #define CLOSE close
  #define OPEN open
#endif

#define SILENT_RUN(func) do {                     \
    fflush(stdout);                            \
    int bak = DUP(FILENO(stdout));              \
    int new_fd = OPEN(DEV_NULL, O_WRONLY);  \
    DUP2(new_fd, FILENO(stdout));               \
    CLOSE(new_fd);                             \
                                               \
    func;                                      \
                                               \
    fflush(stdout);                            \
    DUP2(bak, FILENO(stdout));                  \
    CLOSE(bak);                                \
} while(0)

/**
 * @brief Runner eines Testes
 *
 * @param[in] func Eine Testfunktion
 */
#define RUN_TEST(func) do {                                         \
    passed_asserts = 0;                                             \
    failed_asserts = 0;                                             \
    is_test_failed = false;                                         \
    SEPARATION_LINE;                                                \
    printf(S_RUN "[%d] %s \n", test_number, #func);                 \
    func;                                               \
    if (is_test_failed == 1) {                                      \
        TEST_FAILED(func);                                          \
    } else if (is_test_failed == 0) {                               \
        TEST_PASSED(func);                                          \
    }                                                       \
} while (0)                       

#define TEST_PASSED(func) do {                                  \
    STATUS_MSG(COLOR_GREEN, S_OK, #func);                       \
    passed_tests++;                                             \
    test_number++;                                              \
} while (0)

#define TEST_FAILED(func) do {                                  \
    STATUS_MSG(BG_COLOR_RED, S_FAILED, #func);                  \
    failed_tests++;                                             \
    test_number++;                                              \
} while (0)

#define TEST_ABORT(msg) do {                                    \
    MSG(COLOR_YELLOW, "%s at %s:%d", msg, __FILE__, __LINE__);  \
    STATUS_MSG(BG_COLOR_YELLOW, S_ERROR, "Abort was called.");  \
    test_number++;                                              \
    is_test_failed = 2;                                         \
    return;                                                     \
} while (0)

#define TEST_FOOTER do {                                                        \
    int total_tests = passed_tests + failed_tests;                              \
    float rate = success_rate(passed_tests, failed_tests);                      \
    SEPARATION_LINE_FAT;                                                        \
    if (rate < 100.0) {                                                         \
        printf(COLOR_RED);                                                      \
    }                                                                           \
    printf("TEST SUMMARY FOR: %s - %.1f%%" COLOR_RESET "\n", __FILE__, rate);   \
    printf("Tests: %d total | " COLOR_GREEN "%d passed" COLOR_RESET " | " COLOR_RED "%d failed" COLOR_RESET "\n", \
           total_tests, passed_tests, failed_tests);                            \
    SEPARATION_LINE_FAT;                                                        \
} while (0)

#define ASSERT_PASSED() passed_asserts += 1

#define ASSERT_FAILED(condition) do { MSG(COLOR_RED, "%s is failed (%s:%d)", #condition, __FILE__, __LINE__); \
                        failed_asserts += 1;                                                    \
                        is_test_failed = 1; } while (0)                                                    

#ifdef USE_STANDARD_ASSERT
    #define N_ASSERT(value) do {    \
        assert(value);              \
        ASSERT_PASSED();        \
    } while(0)
#else
    #define N_ASSERT(condition) do {                                                \
        if (condition) {                                                            \
            ASSERT_PASSED();                                                          \
        } else {                                                                    \
            ASSERT_FAILED(condition);                                               \
        }} while (0)
#endif

#endif