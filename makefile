#This is the Makefile for the MamatScript project
CXX = g++
CXXFLAGS = -g -Wall -std=c++0x
CXXLINK = $(CXX)
LIBS =
OBJS = Commands.o LineParser.o main.o MamatScriptEngine.o Matrix.o Scalar.o Variable.o VariablesMap.o
RM = rm -f
# Creating the executable (MamatScript)
MamatScript: $(OBJS)
	$(CXXLINK) -o MamatScript $(OBJS) $(LIBS)

# Creating object files using default rules
Commands.o: Commands.cpp Commands.h VariablesMap.h MySharedPtr.h \
 Variable.h Scalar.h Matrix.h LineParser.h ScriptExceptions.h
LineParser.o: LineParser.cpp LineParser.h VariablesMap.h MySharedPtr.h \
 Variable.h Commands.h Scalar.h Matrix.h ScriptExceptions.h
main.o: main.cpp MamatScriptEngine.h VariablesMap.h MySharedPtr.h \
 Variable.h LineParser.h Commands.h
MamatScriptEngine.o: MamatScriptEngine.cpp MamatScriptEngine.h \
 VariablesMap.h MySharedPtr.h Variable.h LineParser.h Commands.h \
 ScriptExceptions.h
Matrix.o: Matrix.cpp Scalar.h Variable.h MySharedPtr.h Matrix.h \
 ScriptExceptions.h
Scalar.o: Scalar.cpp Scalar.h Variable.h MySharedPtr.h Matrix.h \
 ScriptExceptions.h
Variable.o: Variable.cpp Variable.h MySharedPtr.h ScriptExceptions.h
VariablesMap.o: VariablesMap.cpp VariablesMap.h MySharedPtr.h Variable.h \
 ScriptExceptions.h Scalar.h
# Cleaning old files before new make
clean:
	$(RM) MamatScript *.o *.bak *~ "#"* core
