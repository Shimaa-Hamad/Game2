#include <iostream>

using namespace std;

enum enQuestionLevel {Easy =1 , Med=2 , Hard=3 , Mix=4};
enum enOperationType {Add=1 , Sub=2 , Mult=3 , Div=4 , MixOp=5};

struct stQuestion
{
	short Number1=0; 
	short Number2=0; 
	enOperationType Operationtype; 
	enQuestionLevel QuestionLevel; 
	short playerAnswer=0; 
	short CorrectAnswer=0; 
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions; 
	enOperationType Optype;
	enQuestionLevel QuestionsLevel;
	short NumberOfWrongAnswers=0; 
	short NumberOfRightAnswers=0; 
	bool IsPass = false; 
};

string GetOperationTypeSymbol(enOperationType Optype)
{
	switch (Optype)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevel[4] = { "Easy" , "Med" , "Hard" ,"Mix" };
	return ArrQuestionLevel[QuestionLevel - 1];
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadNumberOfQuestion()
{
	short NumberOfQuestion;
	do
	{
		cout << "How Many Questions Do You Want To Answer : ";
		cin >> NumberOfQuestion; 
	} while (NumberOfQuestion < 1 || NumberOfQuestion>10);
	return NumberOfQuestion; 
}

enOperationType ReadOperationType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type : [1]Add , [2]Sub , [3]Mult , [4]Div , [5]MixOp : ";
		cin >>  OpType;;
	} while (OpType < 1 || OpType>5);
	return (enOperationType)OpType;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel=0;
	do
	{
		cout << "Enter Questions Level : [1]Easy , [2]Med , [3]Hard , [4]Mix : ";
		cin >> QuestionLevel;;
	} while (QuestionLevel < 1 || QuestionLevel>4);
	return (enQuestionLevel)QuestionLevel;
}

short SimpleCalculator(short Number1, short Number2, enOperationType Optype)
{
	switch (Optype)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub :
		return Number1 - Number2; 
	case enOperationType::Mult:
		return Number1 * Number2; 
	case enOperationType :: Div :
		return Number1 / Number2; 
	default :
		return Number1 + Number2;
	}
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GenerateQuestion(enOperationType Optype , enQuestionLevel QuestionLevel)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel=(enQuestionLevel)RandomNumber(1, 3);
	}
	if (Optype == enOperationType::MixOp)
	{
		Optype = GetRandomOperationType();
	}
	Question.Operationtype = Optype; 
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator (Question.Number1 , Question.Number2 , Optype);
		Question.QuestionLevel = QuestionLevel;
		return Question; 
	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Optype);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Optype);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0;Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.Optype, Quizz.QuestionsLevel);
	}
}

short ReadPlayerAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOperationTypeSymbol(Quizz.QuestionList[QuestionNumber].Operationtype);
	cout << "\n----------" << endl;

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].playerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false; 
		Quizz.NumberOfWrongAnswers++;
		cout << "Wrong Answer \n";
		cout << "The Correct Answer = " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl; 
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer\n";
	}
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].playerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "-----------------------------------------------\n\n";
	cout << "Final Results is " << GetFinalResultsText(Quizz.IsPass) << endl; 
	cout << "-----------------------------------------------\n\n";
	cout << "NUmber of Question " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type " << GetOperationTypeSymbol(Quizz.Optype) << endl;
	cout << "Number of Right Answers " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers " << Quizz.NumberOfWrongAnswers << endl; 
	cout << "-----------------------------------------------\n\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadNumberOfQuestion();
	Quizz.Optype = ReadOperationType();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResult(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do You Want To Play Again Y/N \n";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}