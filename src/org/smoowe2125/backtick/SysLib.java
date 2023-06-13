package org.smoowe2125.backtick;

public class SysLib extends Library {
    public SysLib() {
        name = "syslib";
        keywords = new Object[]{"int", "string", "float", "double", "bool", "char", "byte", "short", "long"};
    }

    // Functions
    public int toInt(String obj) {
        return Integer.parseInt(obj);
    }
    public String toStr(Object obj) {
        return (String) obj;
    }
    public float toFloat(Object obj) {
        return (float) obj;
    }
    public double toDouble(Object obj) {
        return (double) obj;
    }
    public boolean toBool(Object obj) {
        return (boolean) obj;
    }
    public char toChar(Object obj) {
        return (char) obj;
    }
    public byte toByte(Object obj) {
        return (byte) obj;
    }
    public short toShort(Object obj) {
        return (short) obj;
    }
    public long toLong(Object obj) {
        return (long) obj;
    }
    public String[] splitStr(String toSplit, String regex) {
        if(regex.equals("")) {
            return toSplit.split("(?!^)");
        }
        return toSplit.split(regex);
    }
    public void initialize() {
        initialized = true;
    }
}
