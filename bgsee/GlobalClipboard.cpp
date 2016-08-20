#include "Main.h"
#include "Console.h"
#include "GlobalClipboard.h"

namespace bgsee
{
	GlobalClipboard*			GlobalClipboard::Singleton = nullptr;
	const char*					GlobalClipboard::kClipboardBufferPath = "bgseegc";

	GlobalClipboard::GlobalClipboard() :
		Operator(nullptr),
		Buffer(nullptr),
		Initialized(false)
	{
		;//
	}

	GlobalClipboard::~GlobalClipboard()
	{
		SAFEDELETE(Operator);
		SAFEDELETE(Buffer);

		Initialized = false;

		Singleton = nullptr;
	}

	GlobalClipboard* GlobalClipboard::GetSingleton()
	{
		if (Singleton == nullptr)
			Singleton = new GlobalClipboard();

		return Singleton;
	}

	bool GlobalClipboard::Initialize( GlobalClipboardOperator* Operator, PluginFileWrapper* PluginWrapper )
	{
		if (Initialized)
			return false;

		SME_ASSERT(Operator && PluginWrapper);

		this->Operator = Operator;
		this->Buffer = PluginWrapper;

		Initialized = Buffer->Construct(kClipboardBufferPath, true);

		return Initialized;
	}

	bool GlobalClipboard::Copy( FormListT& Forms )
	{
		SME_ASSERT(Initialized);

		bool Result = false;

		BGSEECONSOLE_MESSAGE("Copying forms to global clipboard...");
		BGSEECONSOLE->Indent();

		if (Forms.size())
		{
			bool FormCheck = true;
			for (FormListT::iterator Itr = Forms.begin(); Itr != Forms.end(); Itr++)
			{
				if (Operator->GetIsFormTypeReplicable((*Itr)->GetType()) == false)
				{
					BGSEECONSOLE_MESSAGE("Form type error! Type '%s' is not replicable", (*Itr)->GetTypeString());
					FormCheck = false;
					break;
				}
			}

			if (FormCheck)
			{
				FormCollectionSerializer* Serializer = Operator->GetSerializer(Forms);
				if (Serializer)
				{
					Operator->PreCopyCallback(Forms, Buffer);
					Result = Serializer->Serialize(Forms, Buffer);
					Operator->PostCopyCallback(Result);
				}

				if (Result)
					BGSEECONSOLE_MESSAGE("Copied %d forms", Forms.size());
			}

			if (Result == false)
				BGSEEUI->MsgBoxE(nullptr, MB_TASKMODAL|MB_SETFOREGROUND, "Global copy operation failed! Check the console for more information.");

			for (FormListT::iterator Itr = Forms.begin(); Itr != Forms.end(); Itr++)
				delete *Itr;

			Forms.clear();
		}

		BGSEECONSOLE->Exdent();

		return Result;
	}

	bool GlobalClipboard::Paste( bool ClearIfSuccessful /*= false*/ )
	{
		SME_ASSERT(Initialized);

		bool Result = false;

		BGSEECONSOLE_MESSAGE("Pasting forms from global clipboard...");
		BGSEECONSOLE->Indent();

		FormCollectionSerializer* Deserializer = Operator->GetDeserializer(Buffer);
		if (Deserializer == nullptr)
			BGSEECONSOLE_MESSAGE("Unrecognized clipboard buffer serializer/deserializer!");
		else
		{
			int Count = 0;
			Operator->PrePasteCallback(Buffer);
			Result = Deserializer->Deserialize(Buffer, Count);
			Operator->PostPasteCallback(Result, Deserializer);

			if (Result)
				BGSEECONSOLE_MESSAGE("Pasted %d forms", Count);
		}

		if (Result && ClearIfSuccessful)
			Buffer->Purge();

		if (Result == false)
			BGSEEUI->MsgBoxE(nullptr, MB_TASKMODAL|MB_SETFOREGROUND, "Global paste operation failed! Check the console for more information.");

		BGSEECONSOLE->Exdent();

		return Result;
	}

	void GlobalClipboard::DisplayContents( void )
	{
		SME_ASSERT(Initialized);

		Operator->DisplayClipboardContents(Buffer);
	}
}