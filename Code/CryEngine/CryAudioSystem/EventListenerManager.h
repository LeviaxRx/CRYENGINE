// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "SystemRequestData.h"

namespace CryAudio
{
class CEventListenerManager final
{
public:

	CEventListenerManager() = default;
	~CEventListenerManager();

	CEventListenerManager(CEventListenerManager const&) = delete;
	CEventListenerManager(CEventListenerManager&&) = delete;
	CEventListenerManager& operator=(CEventListenerManager const&) = delete;
	CEventListenerManager& operator=(CEventListenerManager&&) = delete;

	ERequestStatus         AddRequestListener(SSystemRequestData<ESystemRequestType::AddRequestListener> const* const pRequestData);
	ERequestStatus         RemoveRequestListener(void (* func)(SRequestInfo const* const), void const* const pObjectToListenTo);
	void                   NotifyListener(SRequestInfo const* const pRequestInfo);

#if defined(INCLUDE_AUDIO_PRODUCTION_CODE)
	size_t GetNumEventListeners() const { return m_listeners.size(); }
#endif //INCLUDE_AUDIO_PRODUCTION_CODE

private:

	struct SEventListener
	{
		SEventListener()
			: pObjectToListenTo(nullptr)
			, OnEvent(nullptr)
			, eventMask(ESystemEvents::None)
		{}

		void const*   pObjectToListenTo;
		void          (* OnEvent)(SRequestInfo const* const);
		ESystemEvents eventMask;
	};

	using ListenerArray = std::vector<SEventListener>;
	ListenerArray m_listeners;
};
} // namespace CryAudio
