include	../make_definitions

#===============================================================================
#	Include files dependencies
#===============================================================================

$(INCLUDE_DIR)/Message.h:						\
		$(COMMON_INCLUDE_DIR)/CommonMessage.h
	$(TOUCH) $@

$(INCLUDE_DIR)/LinearGenerator.h:					\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(INCLUDE_DIR)/LinearGenerator.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/RandomGenerator.h:					\
		$(INCLUDE_DIR)/LinearGenerator.h			\
		$(INCLUDE_DIR)/RandomGenerator.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/Cryptography.h:						\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/Cryptography.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/CandidateVote.h:						\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/Vector.h				\
		$(INCLUDE_DIR)/CandidateVote.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/VotersFile.h:						\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Vector.h				\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/VotersFile.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/VotesFile.h:						\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Vector.h				\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/Cryptography.h				\
		$(INCLUDE_DIR)/VotesFile.inl
	$(TOUCH) $@

$(INCLUDE_DIR)/LocalUtility.h:						\
		$(INCLUDE_DIR)/Parameter.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.inl
	$(TOUCH) $@


#===============================================================================
#	Object files dependencies
#===============================================================================

$(OBJECT_DIR)/LinearGenerator.o: $(SOURCE_DIR)/LinearGenerator.cpp	\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/LinearGenerator.h			\
		$(INCLUDE_DIR)/LinearGenerator.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/LinearGenerator.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/RandomGenerator.o: $(SOURCE_DIR)/RandomGenerator.cpp	\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/RandomGenerator.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/RandomGenerator.cpp		\
		$(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/Cryptography.o: $(SOURCE_DIR)/Cryptography.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Cryptography.h				\
		$(INCLUDE_DIR)/Cryptography.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/Cryptography.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/CandidateVote.o: $(SOURCE_DIR)/CandidateVote.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/CandidateVote.h				\
		$(INCLUDE_DIR)/CandidateVote.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/CandidateVote.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/VotersFile.o: $(SOURCE_DIR)/VotersFile.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Cryptography.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/VotersFile.h				\
		$(INCLUDE_DIR)/VotersFile.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/VotersFile.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/VotesFile.o: $(SOURCE_DIR)/VotesFile.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/VotesFile.h				\
		$(INCLUDE_DIR)/VotesFile.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/VotesFile.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/LocalUtility.o: $(SOURCE_DIR)/LocalUtility.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(COMMON_INCLUDE_DIR)/NumericException.h		\
		$(COMMON_INCLUDE_DIR)/FileManager.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/CharacterManager.h		\
		$(COMMON_INCLUDE_DIR)/SystemManager.h			\
		$(INCLUDE_DIR)/Cryptography.h				\
		$(INCLUDE_DIR)/LocalUtility.h				\
		$(INCLUDE_DIR)/LocalUtility.inl
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/LocalUtility.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/CreateMain.o: $(SOURCE_DIR)/CreateMain.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/FileManager.h			\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/VotersFile.h				\
		$(INCLUDE_DIR)/VotesFile.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/CreateMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/VoteMain.o: $(SOURCE_DIR)/VoteMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/NumericException.h		\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/VotersFile.h				\
		$(INCLUDE_DIR)/VotesFile.h				\
		$(COMMON_INCLUDE_DIR)/File.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/VoteMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/NoiseMain.o: $(SOURCE_DIR)/NoiseMain.cpp			\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/SystemManager.h			\
		$(INCLUDE_DIR)/RandomGenerator.h			\
		$(INCLUDE_DIR)/VotesFile.h				\
		$(COMMON_INCLUDE_DIR)/Utility.h				\
		$(INCLUDE_DIR)/LocalUtility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/NoiseMain.cpp $(OBJECT_NAME_FLAG) $@

$(OBJECT_DIR)/ResultMain.o: $(SOURCE_DIR)/ResultMain.cpp		\
		$(COMMON_INCLUDE_DIR)/Standard.h			\
		$(INCLUDE_DIR)/Parameter.h				\
		$(INCLUDE_DIR)/Message.h				\
		$(COMMON_INCLUDE_DIR)/FatalException.h			\
		$(COMMON_INCLUDE_DIR)/IOException.h			\
		$(COMMON_INCLUDE_DIR)/ApplicationException.h		\
		$(COMMON_INCLUDE_DIR)/ExceptionHandler.h		\
		$(COMMON_INCLUDE_DIR)/GenericString.h			\
		$(COMMON_INCLUDE_DIR)/CharacterManager.h		\
		$(COMMON_INCLUDE_DIR)/SystemManager.h			\
		$(INCLUDE_DIR)/CandidateVote.h				\
		$(INCLUDE_DIR)/VotesFile.h				\
		$(COMMON_INCLUDE_DIR)/Vector.h				\
		$(COMMON_INCLUDE_DIR)/OrderedVector.h			\
		$(COMMON_INCLUDE_DIR)/Utility.h
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/ResultMain.cpp $(OBJECT_NAME_FLAG) $@


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
		$(COMMON_OBJECT_DIR)/SystemManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxSystemManager.o		\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LinearGenerator.o				\
		$(OBJECT_DIR)/RandomGenerator.o				\
		$(OBJECT_DIR)/Cryptography.o				\
		$(OBJECT_DIR)/VotersFile.o				\
		$(OBJECT_DIR)/VotesFile.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(OBJECT_DIR)/CreateMain.o

VOTE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/SystemManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxSystemManager.o		\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LinearGenerator.o				\
		$(OBJECT_DIR)/RandomGenerator.o				\
		$(OBJECT_DIR)/Cryptography.o				\
		$(OBJECT_DIR)/VotersFile.o				\
		$(OBJECT_DIR)/VotesFile.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(OBJECT_DIR)/VoteMain.o

NOISE_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/SystemManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxSystemManager.o		\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LinearGenerator.o				\
		$(OBJECT_DIR)/RandomGenerator.o				\
		$(OBJECT_DIR)/Cryptography.o				\
		$(OBJECT_DIR)/VotesFile.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(OBJECT_DIR)/NoiseMain.o

RESULT_OBJECTS	= $(COMMON_OBJECT_DIR)/ExceptionBase.o			\
		$(COMMON_OBJECT_DIR)/FatalException.o			\
		$(COMMON_OBJECT_DIR)/NumericException.o			\
		$(COMMON_OBJECT_DIR)/IOException.o			\
		$(COMMON_OBJECT_DIR)/ApplicationException.o		\
		$(COMMON_OBJECT_DIR)/ExceptionHandler.o			\
		$(COMMON_OBJECT_DIR)/CharacterManager.o			\
		$(COMMON_OBJECT_DIR)/GenericString.o			\
		$(COMMON_OBJECT_DIR)/SystemManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxSystemManager.o		\
		$(COMMON_OBJECT_DIR)/FileManager.o			\
		$(COMMON_OBJECT_DIR)/LinuxFileManager.o			\
		$(COMMON_OBJECT_DIR)/File.o				\
		$(OBJECT_DIR)/LinearGenerator.o				\
		$(OBJECT_DIR)/RandomGenerator.o				\
		$(OBJECT_DIR)/Cryptography.o				\
		$(OBJECT_DIR)/CandidateVote.o				\
		$(OBJECT_DIR)/VotersFile.o				\
		$(OBJECT_DIR)/VotesFile.o				\
		$(OBJECT_DIR)/LocalUtility.o				\
		$(COMMON_OBJECT_DIR)/Utility.o				\
		$(OBJECT_DIR)/ResultMain.o

#===============================================================================
#	Definitions of programs
#===============================================================================

EXECUTABLES	=	$(EXECUTABLE_DIR)/CreateMajority		\
			$(EXECUTABLE_DIR)/VoteMajority			\
			$(EXECUTABLE_DIR)/NoiseMajority			\
			$(EXECUTABLE_DIR)/ResultMajority


#===============================================================================
#	Programs dependencies
#===============================================================================

$(EXECUTABLE_DIR)/CreateMajority: $(CREATE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(CREATE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/VoteMajority: $(VOTE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(VOTE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/NoiseMajority: $(NOISE_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(NOISE_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@

$(EXECUTABLE_DIR)/ResultMajority: $(RESULT_OBJECTS)
	$(LINK) $(LINK_FLAGS) $(RESULT_OBJECTS) $(EXECUTABLE_NAME_FLAG) $@


#===============================================================================
#	Definitions of global targets
#===============================================================================

all: $(EXECUTABLES)

clean:
	$(DELETE) $(EXECUTABLES) $(CREATE_OBJECTS) $(VOTE_OBJECTS)	\
		$(NOISE_OBJECTS) $(RESULT_OBJECTS)
