#include "RenderSelectionGroupManager.h"
#include "CSDialogs.h"

RenderSelectionGroupManager			g_RenderSelectionGroupManager;

std::vector<TESRenderSelection*>* RenderSelectionGroupManager::GetCellExists(TESObjectCELL* Cell)
{
	_RenderSelectionGroupMap::iterator Match = SelectionGroupMap.find(Cell);
	if (Match != SelectionGroupMap.end())
		return &Match->second;
	else
		return NULL;
}

TESRenderSelection* RenderSelectionGroupManager::GetRefSelectionGroup(TESObjectREFR* Ref, TESObjectCELL* Cell)
{
	TESRenderSelection* Result = NULL;

	std::vector<TESRenderSelection*>* SelectionList = GetCellExists(Cell);
	if (SelectionList)
	{
		for (std::vector<TESRenderSelection*>::iterator Itr = SelectionList->begin(); Itr != SelectionList->end(); Itr++)
		{
			for (TESRenderSelection::SelectedObjectsEntry* ItrEx = (*Itr)->RenderSelection; ItrEx && ItrEx->Data; ItrEx = ItrEx->Next)
			{
				if (ItrEx->Data == Ref)
				{
					Result = *Itr;
					break;
				}
			}
		}
	}

	return Result;
}

void RenderSelectionGroupManager::Clear()
{
	for (_RenderSelectionGroupMap::iterator Itr = SelectionGroupMap.begin(); Itr != SelectionGroupMap.end(); Itr++)
	{
		for (std::vector<TESRenderSelection*>::iterator ItrEx = Itr->second.begin(); ItrEx != Itr->second.end(); ItrEx++)
		{
			thisCall(kTESRenderSelection_ClearSelection, *ItrEx, 0);
			thisCall(kTESRenderSelection_Free, *ItrEx);
			FormHeap_Free(*ItrEx);
		}

		Itr->second.clear();
	}
	SelectionGroupMap.clear();
}

TESRenderSelection* RenderSelectionGroupManager::AllocateNewSelection(TESRenderSelection* Selection)
{
	TESRenderSelection* Group = (TESRenderSelection*)FormHeap_Allocate(0x18);
	thisCall(kCtor_TESRenderSelection, Group);

	for (TESRenderSelection::SelectedObjectsEntry* Itr = Selection->RenderSelection; Itr && Itr->Data; Itr = Itr->Next)
		thisCall(kTESRenderSelection_AddFormToSelection, Group, Itr->Data, 0);

	return Group;
}

TESObjectREFR* RenderSelectionGroupManager::GetRefAtSelectionIndex(TESRenderSelection* Selection, UInt32 Index)
{
	UInt32 Count = 0;
	for (TESRenderSelection::SelectedObjectsEntry* Itr = Selection->RenderSelection; Itr && Itr->Data; Itr = Itr->Next, Count++)
	{
		if (Count == Index)
			return CS_CAST(Itr->Data, TESForm, TESObjectREFR);
	}
	return NULL;
}

TESRenderSelection* RenderSelectionGroupManager::GetTrackedSelection(TESObjectCELL* Cell, TESRenderSelection* Selection)
{
	TESRenderSelection* Result = NULL;

	std::vector<TESRenderSelection*>* SelectionList = GetCellExists(Cell);
	if (SelectionList)
	{
		for (std::vector<TESRenderSelection*>::iterator Itr = SelectionList->begin(); Itr != SelectionList->end(); Itr++)
		{
			TESRenderSelection* Base = *Itr;
			if (Base->SelectionCount == Selection->SelectionCount)
			{
				bool Mismatch = false;
				for (int i = 0; i < Selection->SelectionCount; i++)
				{
					if (GetRefAtSelectionIndex(Selection, i) != GetRefAtSelectionIndex(Base, i))
					{
						Mismatch = true;
						break;
					}
				}
				if (Mismatch)
					break;

				Result = Base;
			}
		}
	}

	return Result;
}

void RenderSelectionGroupManager::UntrackSelection(TESObjectCELL* Cell, TESRenderSelection* TrackedSelection)
{
	std::vector<TESRenderSelection*>* SelectionList = GetCellExists(Cell);
	if (SelectionList)
	{
		std::vector<TESRenderSelection*>::const_iterator EraseItr = SelectionList->end();

		for (std::vector<TESRenderSelection*>::iterator Itr = SelectionList->begin(); Itr != SelectionList->end(); Itr++)
		{
			if (*Itr == TrackedSelection)
			{
				thisCall(kTESRenderSelection_ClearSelection, *Itr, 0);
				thisCall(kTESRenderSelection_Free, *Itr);
				FormHeap_Free(*Itr);

				EraseItr = Itr;
				break;
			}
		}

		if (EraseItr != SelectionList->end())
			SelectionList->erase(EraseItr);
	}
}

bool RenderSelectionGroupManager::AddGroup(TESObjectCELL *Cell, TESRenderSelection *Selection)
{
	bool Result = false;

	std::vector<TESRenderSelection*>* SelectionList = GetCellExists(Cell);
	if (SelectionList)
	{
		bool ExistingGroup = false;
		for (TESRenderSelection::SelectedObjectsEntry* Itr = Selection->RenderSelection; Itr && Itr->Data; Itr = Itr->Next)
		{
			if (GetRefSelectionGroup(CS_CAST(Itr->Data, TESForm, TESObjectREFR), Cell))
			{
				ExistingGroup = true;
				break;
			}
		}

		if (!ExistingGroup)
		{
			TESRenderSelection* Group = AllocateNewSelection(Selection);
			SelectionList->push_back(Group);
			Result = true;
		}
	}
	else
	{
		SelectionGroupMap[Cell] = std::vector<TESRenderSelection*>();

		TESRenderSelection* Group = AllocateNewSelection(Selection);
		SelectionGroupMap[Cell].push_back(Group);
		Result = true;
	}

	return Result;
}

bool RenderSelectionGroupManager::RemoveGroup(TESObjectCELL *Cell, TESRenderSelection *Selection)
{
	bool Result = false;

	std::vector<TESRenderSelection*>* SelectionList = GetCellExists(Cell);
	if (SelectionList)
	{
		TESRenderSelection* TrackedSelection = GetTrackedSelection(Cell, Selection);
		if (TrackedSelection)
		{
			UntrackSelection(Cell, TrackedSelection);
			Result = true;
		}
	}

	return Result;
}