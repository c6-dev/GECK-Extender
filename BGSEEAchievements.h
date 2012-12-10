#pragma once

namespace BGSEditorExtender
{
	namespace Extras
	{
		class BGSEEAchievementManager;

		class BGSEEAchievement
		{
			friend class BGSEEAchievementManager;
		protected:
			enum
			{
				kState_Locked	= 0,
				kState_Unlocked,
				kState_Triggered		// can be used to initiate deferred unlocking
			};

			UUID						BaseID;
			std::string					BaseIDString;
			std::string					Name;
			std::string					Description;
			UInt8						State;
			UInt64						ExtraData;
			UInt32						IconID;

										// called by the manager before unlocking the achievement, return false to remain locked
			virtual bool				UnlockCallback(BGSEEAchievementManager* Parameter);
										// called before the achievement's state is serialized, return false to cancel the save op
			virtual bool				SaveCallback(BGSEEAchievementManager* Parameter);
			
			virtual void				GetName(std::string& OutBuffer) const;
			virtual void				GetDescription(std::string& OutBuffer) const;

			virtual bool				GetUnlockable(void) const;		// only unlockable achievements count towards the total/unlocked achievement count
		public:
			BGSEEAchievement(const char* Name, const char* Desc, UInt32 IconID, const char* GUID);
			virtual ~BGSEEAchievement();

			bool						GetUnlocked(void) const;
			bool						GetTriggered(void) const;
		};

		typedef std::list<BGSEEAchievement*>			ExtenderAchievementListT;

		class BGSEEAchievementManager
		{
			friend class BGSEEAchivement;

			static INT_PTR CALLBACK						NotificationDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			struct NotificationUserData
			{
				BGSEEAchievementManager*				Instance;
				BGSEEAchievement*						Achievement;
				HBRUSH									BGBrush;
				HANDLE									Icon;
			};

			static BGSEEAchievementManager*				Singleton;

			std::string									RegistryKeyRoot;
			std::string									RegistryKeyExtraData;
			ExtenderAchievementListT					AchievementDepot;
			HINSTANCE									ResourceInstance;
			bool										Initialized;

			BGSEEAchievementManager();

			void										SaveAchievementState(BGSEEAchievement* Achievement, bool StateOnly = false);
			void										LoadAchievementState(BGSEEAchievement* Achievement, bool StateOnly = false);

			template <typename T>
			bool										GetRegValue(const char* Name, T* OutValue, const char* Key);
			template <typename T>
			bool										SetRegValue(const char* Name, T Value, const char* Key);
		public:
			~BGSEEAchievementManager();

			static BGSEEAchievementManager*				GetSingleton(void);

														// takes ownership of achievement instances
			bool										Initialize(const char* ExtenderLongName, HINSTANCE ResourceInstance, ExtenderAchievementListT& Achievements);

			void										Unlock(BGSEEAchievement* Achievement, bool ForceUnlock = false, bool TriggerOnly = false, bool PreserveUnlockState = false);
			UInt32										GetTotalAchievements(void) const;
			UInt32										GetUnlockedAchievements(void) const;
		};

#define BGSEEACHIEVEMENTS								BGSEditorExtender::Extras::BGSEEAchievementManager::GetSingleton()
	}
}