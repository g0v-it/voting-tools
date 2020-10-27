include	../make_definitions

#===============================================================================
#	Include files dependencies
#===============================================================================

$(INCLUDE_DIR)/Message.h:						\
		$(COMMON_INCLUDE_DIR)/CommonMessage.h
	$(TOUCH) $@

$(INCLUDE_DIR)/LocalUtility.h:						\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/NumericException.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/Hash.h:							\
		$(INCLUDE_DIR)/Parameter.h
	$(TOUCH) $@

$(INCLUDE_DIR)/Key.h:							\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(INCLUDE_DIR)/State.h
	$(TOUCH) $@

$(INCLUDE_DIR)/State.h:							\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h
	$(TOUCH) $@


#===============================================================================
#	Object files dependencies
#===============================================================================

$(OBJECT_DIR)/LocalUtility.o: $(SOURCE_DIR)/LocalUtility.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/CharacterManager.h		\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/LocalUtility.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/LocalUtility.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/Hash.o: $(SOURCE_DIR)/Hash.cpp				\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/Hash.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/Hash.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/Key.o: $(SOURCE_DIR)/Key.cpp				\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(INCLUDE_DIR)/Key.h					\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/Key.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/State.o: $(SOURCE_DIR)/State.cpp				\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/FileManager.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/Hash.h					\
		$(INCLUDE_DIR)/State.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/State.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/CreateMain.o: $(SOURCE_DIR)/CreateMain.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/FileManager.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/CreateMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/StateMain.o: $(SOURCE_DIR)/StateMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/CharacterManager.h		\
		$(COMMON_INCLUDE_DIR)/Vector.h				\
		$(COMMON_INCLUDE_DIR)/OrderedVector.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/State.h					\
		$(INCLUDE_DIR)/Key.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/StateMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/StartMain.o: $(SOURCE_DIR)/StartMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/State.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/StartMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/VoteMain.o: $(SOURCE_DIR)/VoteMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/Hash.h					\
		$(INCLUDE_DIR)/State.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/VoteMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/CloseMain.o: $(SOURCE_DIR)/CloseMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/FileManager.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/Hash.h					\
		$(INCLUDE_DIR)/Key.h					\
		$(INCLUDE_DIR)/State.h					\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/CloseMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/HashMain.o: $(SOURCE_DIR)/HashMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/Hash.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/HashMain.cpp $(OBJECT_NAME_FLAG) $@


#===============================================================================
#	Definitions of group of objects
#===============================================================================

CREATE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/CreateMain.o

STATE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/Hash.o					\
		$(OBJECT_DIR)/State.o					\
		$(OBJECT_DIR)/Key.o					\
		$(OBJECT_DIR)/StateMain.o

START_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/State.o					\
		$(OBJECT_DIR)/Hash.o					\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/StartMain.o

VOTE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/Hash.o					\
		$(OBJECT_DIR)/State.o					\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/VoteMain.o

CLOSE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/Hash.o					\
		$(OBJECT_DIR)/Key.o					\
		$(OBJECT_DIR)/State.o					\
		$(OBJECT_DIR)/CloseMain.o

HASH_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/Hash.o					\
		$(OBJECT_DIR)/HashMain.o


#===============================================================================
#	Definitions of programs
#===============================================================================

EXECUTABLES	=	$(EXECUTABLE_DIR)/CreateRandom			\
			$(EXECUTABLE_DIR)/StateRandom			\
			$(EXECUTABLE_DIR)/StartRandom			\
			$(EXECUTABLE_DIR)/VoteRandom			\
			$(EXECUTABLE_DIR)/CloseRandom			\
			$(EXECUTABLE_DIR)/HashRandom


#===============================================================================
#	Programs dependencies
#===============================================================================

$(EXECUTABLE_DIR)/CreateRandom: $(CREATE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(CREATE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/StateRandom: $(STATE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(STATE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/StartRandom: $(START_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(START_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/VoteRandom: $(VOTE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(VOTE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/CloseRandom: $(CLOSE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(CLOSE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/HashRandom: $(HASH_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(HASH_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@


#===============================================================================
#	Definitions of global targets
#===============================================================================

all: $(EXECUTABLES)

clean:
	$(DELETE) $(EXECUTABLES) $(CREATE_OBJECTS) $(STATE_OBJECTS)	\
		$(START_OBJECTS) $(VOTE_OBJECTS) $(CLOSE_OBJECTS)	\
		$(HASH_OBJECTS)
