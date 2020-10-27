include	../make_definitions

#===============================================================================
#	Include files dependencies
#===============================================================================

$(INCLUDE_DIR)/ExceptionBase.h:						\
		$(INCLUDE_DIR)/ExceptionBase.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/GenericException.h:					\
		$(INCLUDE_DIR)/ExceptionBase.h				\
		$(INCLUDE_DIR)/GenericException.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/FatalException.h:					\
		$(INCLUDE_DIR)/GenericException.h
	$(TOUCH) $@

$(INCLUDE_DIR)/IOException.h:						\
		$(INCLUDE_DIR)/GenericException.h			\
		$(INCLUDE_DIR)/GenericString.h				\
		$(INCLUDE_DIR)/IOException.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/NumericException.h:					\
		$(INCLUDE_DIR)/GenericException.h
	$(TOUCH) $@

$(INCLUDE_DIR)/ApplicationException.h:					\
		$(INCLUDE_DIR)/GenericException.h			\
		$(INCLUDE_DIR)/ApplicationException.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/ExceptionHandler.h:					\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/ApplicationException.h			\
		$(INCLUDE_DIR)/ExceptionHandler.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/Vector.h:						\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/Vector.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/OrderedVector.h:						\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/Vector.h					\
		$(INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/OrderedVector.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/CharacterManager.h:					\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/CharacterManager.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/GenericString.h:						\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/NumericException.h			\
		$(INCLUDE_DIR)/Vector.h					\
		$(INCLUDE_DIR)/CharacterManager.h			\
		$(INCLUDE_DIR)/GenericString.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/SystemManager.h:						\
		$(INCLUDE_DIR)/SystemManager.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/LinuxSystemManager.h:					\
		$(INCLUDE_DIR)/SystemManager.h				\
		$(INCLUDE_DIR)/LinuxSystemManager.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/ActualSystemManager.h:					\
		$(INCLUDE_DIR)/LinuxSystemManager.h
	$(TOUCH) $@

$(INCLUDE_DIR)/FileManager.h:						\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/Vector.h					\
		$(INCLUDE_DIR)/GenericString.h				\
		$(INCLUDE_DIR)/FileManager.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/LinuxFileManager.h:					\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/Vector.h					\
		$(INCLUDE_DIR)/GenericString.h				\
		$(INCLUDE_DIR)/FileManager.h				\
		$(INCLUDE_DIR)/LinuxFileManager.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/ActualFileManager.h:					\
		$(INCLUDE_DIR)/LinuxFileManager.h
	$(TOUCH) $@

$(INCLUDE_DIR)/File.h:							\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/GenericString.h				\
		$(INCLUDE_DIR)/FileManager.h				\
		$(INCLUDE_DIR)/File.inl					\
		$(INCLUDE_DIR)/File.tpl
	$(TOUCH) $@

$(INCLUDE_DIR)/Utility.h:						\
		$(INCLUDE_DIR)/FatalException.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/ApplicationException.h			\
		$(INCLUDE_DIR)/GenericString.h				\
		$(INCLUDE_DIR)/Utility.inl
	$(TOUCH) $@


#===============================================================================
#	Object files dependencies
#===============================================================================

$(OBJECT_DIR)/ExceptionBase.o: $(SOURCE_DIR)/ExceptionBase.cpp		\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/ExceptionBase.h				\
		$(INCLUDE_DIR)/ExceptionBase.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/ExceptionBase.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/FatalException.o: $(SOURCE_DIR)/FatalException.cpp	\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/FatalException.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/FatalException.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/IOException.o: $(SOURCE_DIR)/IOException.cpp		\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/IOException.h				\
		$(INCLUDE_DIR)/IOException.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/IOException.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/NumericException.o: $(SOURCE_DIR)/NumericException.cpp	\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/NumericException.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/NumericException.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/ApplicationException.o:					\
		$(SOURCE_DIR)/ApplicationException.cpp			\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/ApplicationException.h			\
		$(INCLUDE_DIR)/ApplicationException.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/ApplicationException.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/ExceptionHandler.o:					\
		$(SOURCE_DIR)/ExceptionHandler.cpp			\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/CommonMessage.h				\
		$(INCLUDE_DIR)/File.h					\
		$(INCLUDE_DIR)/ExceptionHandler.h			\
		$(INCLUDE_DIR)/ExceptionHandler.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/ExceptionHandler.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/CharacterManager.o: $(SOURCE_DIR)/CharacterManager.cpp	\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/CharacterManager.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/CharacterManager.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/GenericString.o: $(SOURCE_DIR)/GenericString.cpp		\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/GenericString.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/GenericString.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/SystemManager.o: $(SOURCE_DIR)/SystemManager.cpp		\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/ActualSystemManager.h			\
		$(INCLUDE_DIR)/SystemManager.h				\
		$(INCLUDE_DIR)/SystemManager.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/SystemManager.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/LinuxSystemManager.o:					\
		$(SOURCE_DIR)/LinuxSystemManager.cpp			\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/LinuxSystemManager.h			\
		$(INCLUDE_DIR)/LinuxSystemManager.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/LinuxSystemManager.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/FileManager.o: $(SOURCE_DIR)/FileManager.cpp		\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/FileManager.h				\
		$(INCLUDE_DIR)/FileManager.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/FileManager.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/LinuxFileManager.o: $(SOURCE_DIR)/LinuxFileManager.cpp	\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/LinuxFileManager.h			\
		$(INCLUDE_DIR)/LinuxFileManager.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/LinuxFileManager.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/File.o: $(SOURCE_DIR)/File.cpp				\
		$(INCLUDE_DIR)/Standard.h				\
		$(INCLUDE_DIR)/File.h					\
		$(INCLUDE_DIR)/File.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/File.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/Utility.o: $(SOURCE_DIR)/Utility.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/CommonMessage.h				\
		$(INCLUDE_DIR)/ExceptionHandler.h			\
		$(INCLUDE_DIR)/CharacterManager.h			\
		$(INCLUDE_DIR)/FileManager.h				\
		$(INCLUDE_DIR)/File.h					\
		$(INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/Utility.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/Utility.cpp $(OBJECT_NAME_FLAG) $@


#===============================================================================
#	Definitions of objects
#===============================================================================

OBJECTS	=	$(OBJECT_DIR)/ExceptionBase.o				\
		$(OBJECT_DIR)/FatalException.o				\
		$(OBJECT_DIR)/IOException.o				\
		$(OBJECT_DIR)/NumericException.o			\
		$(OBJECT_DIR)/ApplicationException.o			\
		$(OBJECT_DIR)/ExceptionHandler.o			\
		$(OBJECT_DIR)/CharacterManager.o			\
		$(OBJECT_DIR)/GenericString.o				\
		$(OBJECT_DIR)/SystemManager.o				\
		$(OBJECT_DIR)/LinuxSystemManager.o			\
		$(OBJECT_DIR)/FileManager.o				\
		$(OBJECT_DIR)/LinuxFileManager.o			\
		$(OBJECT_DIR)/File.o					\
		$(OBJECT_DIR)/Utility.o


#===============================================================================
#	Definitions of global targets
#===============================================================================

all: $(OBJECTS)

clean:
	$(DELETE) $(OBJECTS)
