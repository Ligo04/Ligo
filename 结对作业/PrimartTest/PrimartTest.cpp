#include "pch.h"
#include "CppUnitTest.h"
#include"../PrimaryArithMetic/PriAriCreator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrimartTest
{
	TEST_CLASS(PrimartTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(10,10);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}
		TEST_METHOD(TestMethod2)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(100, 100);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}
		TEST_METHOD(TestMethod3)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(100, 10);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}

		TEST_METHOD(TestMethod4)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(1000, 1000);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}

		TEST_METHOD(TestMethod5)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(1000, 10, 6, 10);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}
		TEST_METHOD(TestMethod6)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(1000, 10, 6, 50);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}
		TEST_METHOD(TestMethod7)
		{
			//验证正确的文件（含错误答案）
			PriAriCreator* Par = new PriAriCreator();
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises1.txt", "Answers1.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}
		TEST_METHOD(TestMethod8)
		{
			//验证不存在的文件
			PriAriCreator* Par = new PriAriCreator();
			Assert::IsFalse(Par->ReadTitilesAndAnswer("Exercises2.txt", "Answers2.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises2.txt", "Answers2.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}

		TEST_METHOD(TestMethod9)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(10000, 10);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}

		TEST_METHOD(TestMethod10)
		{
			PriAriCreator* Par = new PriAriCreator();
			Par->CreateAriTitlesAndAnswer(10000, 100);
			Assert::IsTrue(Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"));
			if (Par->ReadTitilesAndAnswer("Exercises.txt", "Answers.txt"))
			{
				Par->VerificationAnswer();
			}
			delete Par;
		}

	};
}
