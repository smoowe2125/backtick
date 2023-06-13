package org.smoowe2125.backtick;

import java.util.ArrayList;
import java.util.Arrays;

public class Interpreter {
    Object[] arr = {};
    public ArrayList<Object> varList = new ArrayList<>(Arrays.asList(arr));
    public RuntimeException libraryNotInitialized(String keyword) {
        return new RuntimeException("The library containing the keyword (if it exists) " + keyword + " is not initialized!");
    }
    public Exception wrongamountof(String character) {
        return new Exception("You put a wrong amount of '" + character + "'!");
    }
    public Exception argmustbetype(String type) {
        return new Exception("Argument passed to function must be type " + type + "!");
    }
    public void interpret(Object[] statements, SysLib syslib, SysIO sysio) throws Exception {
        for(int i = 0; i < statements.length; i++) {
            Exception datatypestack = new Exception("You can't stack data types!");
            Exception existingMethodAsName = new Exception("You can't name variables after functions // You can't include special symbols in variable name!");
            ArrayIndexOutOfBoundsException arroutofbounds = new ArrayIndexOutOfBoundsException("Something went wrong with assigning the value of a variable");
            WordDivider divider = new WordDivider();

            if(syslib.initialized) {
                if(statements[i].equals("int") || statements[i].equals("string") || statements[i].equals("float") || statements[i].equals("double") || statements[i].equals("char") || statements[i].equals("bool") || statements[i].equals("byte") || statements[i].equals("short") || statements[i].equals("long")) {
                    if(statements[i + 2].equals("int")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("float")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("double")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("bool")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("char")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("byte")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("short")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("long")) {
                        throw datatypestack;
                    } else if(statements[i + 2].equals("string")) {
                        throw datatypestack;
                    } else {
                        varList.add(statements[i]);
                        varList.add(statements[i + 2]);
                        try {
                            if(statements[i + 6].equals("'")) {
                                int q = 7;
                                try {
                                    String toSave = "";
                                    while (!statements[i + q].equals("'")) {
                                        toSave += statements[i + q];
                                        if(statements[i + q].equals("")) {
                                            toSave += " ";
                                        }
                                        q++;
                                    }
                                    varList.add(toSave);
                                } catch (ArrayIndexOutOfBoundsException ex) {
                                    q--;
                                }
                            } else {
                                varList.add(statements[i + 6]);
                            }
                        } catch (ArrayIndexOutOfBoundsException e) {
                            throw arroutofbounds;
                        }
                    }
//                    sysio.println("Variables: " + varList);
                } else if(statements[i].equals(":")) {
                    if(statements[i + 1].equals("toInt")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 3].equals("'")) {
                                int q = 4;
                                String toSave = "";
                                try {
                                    while (!statements[i + q].equals("'")) {
                                        toSave += statements[i + q];
                                        q++;
                                    }
                                } catch (ArrayIndexOutOfBoundsException exc) {
                                    q--;
                                }
                                syslib.toInt(toSave);
                            } else {
                                throw argmustbetype("string or char");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toStr")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toStr(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toFloat")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toFloat(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toDouble")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toDouble(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toBool")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toBool(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toChar")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toChar(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toByte")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toByte(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toShort")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toShort(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("toLong")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 4].equals(")")) {
                                syslib.toLong(statements[i + 3]);
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    } else if(statements[i + 1].equals("splitStr")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 7].equals(")")) {
                                syslib.splitStr(statements[i + 3].toString(), statements[i + 6].toString());
                            } else {
                                throw wrongamountof(")");
                            }
                        } else {
                            throw wrongamountof("(");
                        }
                    }
                }
            } else {
                if(statements[i].equals("int") || statements[i].equals("string") || statements[i].equals("float") || statements[i].equals("double") || statements[i].equals("char") || statements[i].equals("byte") || statements[i].equals("short") || statements[i].equals("long")) {
                    throw libraryNotInitialized(statements[i].toString());
                }
            }
            if(sysio.initialized) {
                if(statements[i].equals(":")) {
                    if(statements[i + 1].equals("print")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 3].equals("'")) {
                                int q = 4;
                                String toSave = "";
                                try {
                                    while (!statements[i + q].equals("'")) {
                                        toSave += statements[i + q];
                                        if(statements[i + q].equals("")) {
                                            toSave += " ";
                                        }
                                        q++;
                                    }
                                } catch (ArrayIndexOutOfBoundsException exc) {
                                    q--;
                                }
                                sysio.print(toSave);
                            } else {
                                throw argmustbetype("string or char");
                            }
                        }
                    } else if(statements[i + 1].equals("println")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 3].equals("'")) {
                                int q = 4;
                                String toSave = "";
                                try {
                                    while (!statements[i + q].equals("'")) {
                                        toSave += statements[i + q];
                                        if(statements[i + q].equals("")) {
                                            toSave += " ";
                                        }
                                        q++;
                                    }
                                } catch (ArrayIndexOutOfBoundsException exc) {
                                    q--;
                                }
                                sysio.println(toSave);
                            } else {
                                if(varList.contains(statements[i + 3])) {
                                    int index = varList.indexOf(statements[i + 3]) + 1;
                                    // Ty debilu to jest podstawa println nie usuwaj
                                    sysio.println(varList.get(index));
                                }
                            }
                        }
                    } else if(statements[i + 1].equals("input")) {
                        if(statements[i + 2].equals("(")) {
                            if(statements[i + 3].equals("'")) {
                                int q = 4;
                                String toSave = "";
                                try {
                                    while (!statements[i + q].equals("'")) {
                                        toSave += statements[i + q];
                                        if(statements[i + q].equals("")) {
                                            toSave += " ";
                                        }
                                        q++;
                                    }
                                    if(!statements[i + q + 1].equals(")")) {
                                        throw wrongamountof(")");
                                    } else {
                                        int index = varList.indexOf(statements[i]);
                                        varList.set(index, sysio.input(toSave));
                                    }
                                } catch (ArrayIndexOutOfBoundsException exc) {
                                    q--;
                                }
                            }
                        }
                    }
                }
            } else {

            }

        }
    }
}
