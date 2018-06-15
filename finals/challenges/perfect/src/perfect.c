#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main() {
    char input_str[1024];
    mpz_t total, mod, inc, use, target;
    int flag;

    mpz_init(total);
    mpz_set_ui(total, 0);

    mpz_init(mod);
    mpz_set_ui(mod, 0);

    mpz_init(inc);
    mpz_set_ui(inc, 0);

    mpz_init(use);
    mpz_set_ui(use, 0);

    mpz_init(target);
    mpz_set_ui(target, 0x2);
    mpz_mul_2exp(target, target, 212);

    printf("Eschucha? ");
    scanf("%1023s", input_str);

    flag = mpz_set_str(inc, input_str, 10);
    assert(flag == 0);
    mpz_sub_ui(inc, inc, 1);
    flag = mpz_set_str(use, input_str, 10);
    assert(flag == 0);

    while (mpz_cmp_ui(inc, 0) != 0) {
        mpz_mod(mod, use, inc);
        if (mpz_cmp_ui(mod, 0) == 0) {
            mpz_add(total, total, inc);
        }
        mpz_sub_ui(inc, inc, 1);
    }

    if (mpz_cmp(use, total) == 0 && mpz_cmp(use, target) > 0) {
        printf("random.seed(");
        mpz_out_str(stdout, 10, total);
        puts(")");
        puts("k = \"\".join([chr(random.randint(0, 255)) for i in range(35)])");
        puts("xor(k, 754e26ccd4b1bfafb3ffbdaa748780b7f0e0c3ae9acc3c008670f0fafd34f8ffa596db)");
    }

    mpz_clear(total);
    mpz_clear(use);
    mpz_clear(inc);
    mpz_clear(mod);
    mpz_clear(target);
}
