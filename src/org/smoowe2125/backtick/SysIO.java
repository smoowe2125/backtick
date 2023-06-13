package org.smoowe2125.backtick;

import java.util.Scanner;

public class SysIO extends Library {
    public SysIO() {
        name = "sysio";
    }

    public void print(Object o) {
        System.out.print(o);
    }
    public void println(Object o) {
        System.out.println(o);
    }
    public Object input(String msg) {
        print(msg);
        Object o;
        Scanner sc = new Scanner(System.in);
        o = sc.nextLine();
        return o;
    }
    public void initialize() {
        initialized = true;
    }
}
