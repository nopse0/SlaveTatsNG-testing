#include <SlaveTatsNG_Interface.h>

namespace
{
	void messaging_hook([[maybe_unused]] SKSE::MessagingInterface::Message* a_message)
	{
		switch (a_message->type) {
		case SKSE::MessagingInterface::kPostLoad:
		{
			const char* slavetatsPlugin = "SlaveTatsNG";
			SKSE::GetMessagingInterface()->RegisterListener(slavetatsPlugin, [](SKSE::MessagingInterface::Message* a_msg) {
				// logger::info("a_msg={}, msgtype={}, message_root_interface={}", (void*)a_msg, a_msg ? a_msg->type : -1, (int)jc::message_root_interface);
				if (a_msg && a_msg->type == SlaveTatsNG::MessageType::Interface) {
					const SlaveTatsNG::Addresses* iface = SlaveTatsNG::Addresses::from_void(a_msg->data);
					logger::info("SlaveTatsNG Interface found: address = {}", (void*)iface);
					logger::info("simple_add_tattoo: address = {}", (void*)iface->simple_add_tattoo);
				}
			});
		}
		}
	}

	void initialize_logging()
	{
		auto path = logger::log_directory();
		if (!path) {
			stl::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format(FMT_STRING("{}.log"), Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

		log->set_level(spdlog::level::info);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%H:%M:%S:%e] %v"s);

		logger::info(FMT_STRING("{} v{}"), Plugin::NAME, Plugin::VERSION.string());
	}
}


extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() noexcept {
	SKSE::PluginVersionData v;
	v.PluginName(Plugin::NAME.data());
	v.PluginVersion(Plugin::VERSION);
	v.UsesAddressLibrary();
	v.UsesNoStructs();
	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query([[maybe_unused]] const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->name = SKSEPlugin_Version.pluginName;
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->version = SKSEPlugin_Version.pluginVersion;
	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	SKSE::Init(a_skse);

	initialize_logging();

	logger::info("Game version : {}", a_skse->RuntimeVersion().string());

	const auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener(messaging_hook);

	return true;
}
