/*
 * Command for accessing onboard LED.
 *
 */

#include <common.h>
#include <asm/io.h>

extern void led1_red_on(void);
extern void led1_green_on(void);
extern void led1_red_off(void);
extern void led1_green_off(void);
extern void led2_red_on(void);
extern void led2_green_on(void);
extern void led2_red_off(void);
extern void led2_green_off(void);

static int do_led_on(int argc, char *argv[])
{
    int id = 0;
    const char *color;

    if(argc != 3)
        goto usage;

    id = (int)simple_strtol(argv[1], NULL, 10);
    color = argv[2];

    if (strcmp(color, "red") == 0) {

        switch(id) {
        case 1:
            led1_red_on();
            break;
        case 2:
            led2_red_on();
            break;
        }
    }

    if (strcmp(color, "green") == 0) {
        switch(id) {
        case 1:
            led1_green_on();
            break;
        case 2:
            led2_green_on();
            break;
        }
    }

    return 0;

usage:
    printf("usage: led on <led_id> <color>\n");
    return 1;
}

static int do_led_off(int argc, char *argv[])
{
    int id = 0;

    if(argc != 2)
        goto usage;

    id = (int)simple_strtol(argv[1], NULL, 10);

    switch(id) {
    case 1:
        led1_red_off();
        break;
    case 2:
        led1_green_off();
        break;
    }

    return 0;

usage:
    printf("usage: led off <led_id>\n");
    return 1;
}

static int do_led(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    const char *cmd;

    /* need at least two arguments */
    if (argc < 2)
        goto usage;

    cmd = argv[1];

    if (strcmp(cmd, "on") == 0)
        return do_led_on(argc - 1, argv + 1);
    if (strcmp(cmd, "off") == 0)
        return do_led_off(argc - 1, argv + 1);

usage:
    cmd_usage(cmdtp);
    return 1;
}

U_BOOT_CMD(
    led, 4, 0, do_led,
    "drive fm403c led's",
    "led on <led_id> <color> - on given led_id\n"
    "led off <led_id> - off given led_id\n"
    );
