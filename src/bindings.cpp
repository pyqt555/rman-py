#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
#include <thread>
#include <memory>
#include "rman_dl.hpp"
#include "rbun_chk.hpp"
#include "rbun_ex.hpp"
#include "rbun_ls.hpp"
#include "rbun_merge.hpp"
#include "rbun_usage.hpp"
#include "rman_bl.hpp"
#include "rman_chk.hpp"
#include "rman_diff.hpp"
#include "rman_ls.hpp"
#include "rman_make.hpp"
#include "rman_merge.hpp"
#include "rman_remake.hpp"
#include "rman_rads.hpp"
#include "rman_mount.hpp"




namespace py = pybind11;


std::optional<std::regex> make_regex(const std::optional<std::string>& pattern) {
    if (!pattern || pattern->empty()) {
        return std::nullopt;
    }
    try {
        return std::regex{*pattern, std::regex::optimize | std::regex::icase};
    } catch (const std::regex_error& e) {
        throw py::value_error("Invalid regex pattern: " + std::string(e.what()));
    }
}


void download(
    std::string manifest,
    std::string output = ".",
    std::string update = "",
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt,
    bool no_verify = false,
    bool no_write = false,
    bool no_progress = false,

    // Cache Options
    std::string cache_path = "",
    bool cache_readonly = false,
    bool cache_newonly = false,
    uint32_t cache_buffer_mib = 32,
    uint32_t cache_limit_gib = 4,

    // CDN Options
    std::string cdn_url = "http://lol.secure.dyn.riotcdn.net/channels/public",
    size_t cdn_lowspeed_time = 0,
    size_t cdn_lowspeed_kbps = 64,
    uint32_t cdn_retry = 3,
    uint32_t cdn_workers = 32,
    int cdn_interval_ms = 100,
    bool cdn_verbose = false,
    long cdn_buffer_kb = 512,
    std::string cdn_proxy = "",
    std::string cdn_useragent = "",
    std::string cdn_cookiefile = "",
    std::string cdn_cookielist = ""
) {
    RmanDl app;


    app.cli.manifest = manifest;
    app.cli.output = output;
    app.cli.updatefrommanfiest = update;
    app.cli.no_verify = no_verify;
    app.cli.no_write = no_write;
    app.cli.no_progress = no_progress;


    app.cli.match.langs = make_regex(filter_lang);
    app.cli.match.path = make_regex(filter_path);


    app.cli.cache.path = cache_path;
    app.cli.cache.readonly = cache_readonly;
    app.cli.cache.newonly = cache_newonly;
    app.cli.cache.flush_size = cache_buffer_mib * rlib::MiB;
    app.cli.cache.max_size = (std::uint64_t)cache_limit_gib * rlib::GiB;


    app.cli.cdn.url = rlib::clean_path(cdn_url);
    app.cli.cdn.low_speed_time = cdn_lowspeed_time;
    app.cli.cdn.low_speed_limit = cdn_lowspeed_kbps * rlib::KiB;
    app.cli.cdn.retry = cdn_retry;
    app.cli.cdn.workers = cdn_workers;
    app.cli.cdn.interval = cdn_interval_ms;
    app.cli.cdn.verbose = cdn_verbose;
    app.cli.cdn.buffer = cdn_buffer_kb * 1024;
    app.cli.cdn.proxy = cdn_proxy;
    app.cli.cdn.useragent = cdn_useragent;
    app.cli.cdn.cookiefile = cdn_cookiefile;
    app.cli.cdn.cookielist = cdn_cookielist;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void bundle_check(
    std::vector<std::string> inputs,
    bool no_hash = false,
    bool no_extract = false,
    bool no_progress = false,
    uint32_t parallel = 0
) {
    RbunChk app;


    app.cli.inputs = inputs;
    app.cli.no_hash = no_hash;
    app.cli.no_extract = no_extract;
    app.cli.no_progress = no_progress;
    app.cli.parallel = parallel;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void bundle_extract(
    std::string output,
    std::vector<std::string> inputs,
    bool with_offset = false,
    bool force = false,
    bool no_hash = false,
    bool no_progress = false
) {
    RbunEx app;

    app.cli.output = output;
    app.cli.inputs = inputs;
    app.cli.with_offset = with_offset;
    app.cli.force = force;
    app.cli.no_hash = no_hash;
    app.cli.no_progress = no_progress;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}




void bundle_list(
    std::vector<std::string> inputs,
    std::string format = "{bundleId},{chunkId},{compressedSize},{uncompressedSize}"
) {
    RbunLs app;

    app.cli.inputs = inputs;
    app.cli.format = format;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void bundle_merge(
    std::string output,
    std::vector<std::string> inputs,
    int level_recompress = 0,
    bool no_extract = false,
    bool no_progress = false,
    bool newonly = false,
    uint32_t buffer_mib = 32,
    uint32_t limit_gib = 4096
) {
    RbunMerge app;

    app.cli.inputs = inputs;
    app.cli.level_recompress = std::clamp(level_recompress, -7, 22);
    app.cli.no_extract = no_extract;
    app.cli.no_progress = no_progress;


    app.cli.output.path = output;
    app.cli.output.newonly = newonly;
    app.cli.output.flush_size = buffer_mib * rlib::MiB;
    app.cli.output.max_size = (std::uint64_t)limit_gib * rlib::GiB;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void bundle_usage(std::vector<std::string> inputs) {
    RbunUsage app;
    app.cli.inputs = inputs;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_bundle_list(
    std::vector<std::string> inputs,
    std::string format = "/{bundleId}.bundle"
) {
    RmanBl app;
    app.cli.inputs = inputs;
    app.cli.format = format;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_check(
    std::string manifest,
    std::string bundle
) {
    RmanChk app;
    app.cli.inmanifest = manifest;
    app.cli.inbundle = bundle;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_diff(
    std::string output,
    std::string from_manifest,
    std::string into_manifest,
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt
) {
    RmanDiff app;
    app.cli.outmanifset = output;
    app.cli.frommanifest = from_manifest;
    app.cli.intomanifest = into_manifest;


    app.cli.match.langs = make_regex(filter_lang);
    app.cli.match.path = make_regex(filter_path);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_list(
    std::string manifest,
    std::string format = "{path},{size},{fileId},{langs}",
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt
) {
    RmanLs app;
    app.cli.manifest = manifest;
    app.cli.format = format;


    app.cli.match.langs = make_regex(filter_lang);
    app.cli.match.path = make_regex(filter_path);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_make(
    std::string output_manifest,
    std::string output_bundle,
    std::string root_folder,
    std::vector<std::string> inputs = {},
    bool append = false,
    bool no_progress = false,
    bool strip_chunks = false,
    std::string cdc_algo = "fixed",
    std::string no_ar = "",
    bool ar_strict = false,
    uint32_t ar_min_kb = 4,
    uint32_t chunk_size_kb = 1024,
    int32_t level = 6,
    int32_t level_high_entropy = 0,
    bool newonly = false,
    uint32_t buffer_mib = 32,
    uint32_t limit_gib = 4096
) {
    RmanMake app;


    app.cli.outmanifest = output_manifest;
    app.cli.rootfolder = root_folder;
    app.cli.inputs = inputs;


    if (app.cli.inputs.empty() && !app.cli.rootfolder.empty()) {
        app.cli.inputs.push_back(app.cli.rootfolder);
    }

    app.cli.append = append;
    app.cli.no_progress = no_progress;
    app.cli.strip_chunks = strip_chunks;
    app.cli.level = level;
    app.cli.level_high_entropy = level_high_entropy;


    app.cli.outbundle = {
        .path = output_bundle,
        .newonly = newonly,
        .flush_size = buffer_mib * rlib::MiB,
        .max_size = (std::uint64_t)limit_gib * rlib::GiB,
    };


    app.cli.ar = Ar{
        .chunk_min = ar_min_kb * rlib::KiB,
        .chunk_max = chunk_size_kb * rlib::KiB,
        .disabled = Ar::PROCESSOR_PARSE(no_ar),
        .cdc = Ar::PROCESSOR_PARSE(cdc_algo, true),
        .strict = ar_strict,
    };

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_merge(
    std::string output,
    std::vector<std::string> manifests,
    std::string cache_path = "",
    bool cache_newonly = false,
    uint32_t cache_buffer_mib = 32,
    uint32_t cache_limit_gib = 4096,
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt,
    bool strip_chunks = false,
    bool with_prefix = false
) {
    RmanMerge app;
    app.cli.output = output;
    app.cli.manifests = manifests;


    app.cli.match.langs = make_regex(filter_lang);
    app.cli.match.path = make_regex(filter_path);


    app.cli.cache = {
        .path = cache_path,
        .readonly = false,
        .newonly = cache_newonly,
        .flush_size = cache_buffer_mib * rlib::MiB,
        .max_size = (std::uint64_t)cache_limit_gib * rlib::GiB,
    };


    app.cli.strip_chunks = strip_chunks;
    app.cli.with_prefix = with_prefix;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}


void manifest_remake(
    std::string out_bundle,
    std::string out_manifest,
    std::string in_bundle,
    std::vector<std::string> in_manifests,
    std::string resume_file = "",
    uint32_t resume_buffer_kb = 64,
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt,
    bool append = false,
    bool no_progress = false,
    bool strip_chunks = false,
    bool with_prefix = false,
    std::string cdc_algo = "fixed",
    std::string no_ar = "",
    bool ar_strict = false,
    uint32_t ar_min_kb = 4,
    uint32_t chunk_size_kb = 1024,
    int32_t level = 6,
    int32_t level_high_entropy = 0,
    bool newonly = false,
    uint32_t buffer_mib = 32,
    uint32_t limit_gib = 4096
) {
    RmanRemake app;


    app.cli.outmanifest = out_manifest;
    app.cli.outbundle = {
        .path = out_bundle,
        .newonly = newonly,
        .flush_size = buffer_mib * rlib::MiB,
        .max_size = (std::uint64_t)limit_gib * rlib::GiB,
    };
    app.cli.inbundle = { .path = in_bundle, .readonly = true };
    app.cli.inmanifests = in_manifests;


    app.cli.resume_file = resume_file;
    app.cli.resume_buffer = resume_buffer_kb * rlib::KiB;

    app.cli.match.langs = make_regex(filter_lang);
    app.cli.match.path = make_regex(filter_path);


    app.cli.append = append;
    app.cli.no_progress = no_progress;
    app.cli.strip_chunks = strip_chunks;
    app.cli.with_prefix = with_prefix;
    app.cli.level = level;
    app.cli.level_high_entropy = level_high_entropy;


    app.cli.ar = Ar{
        .chunk_min = ar_min_kb * rlib::KiB,
        .chunk_max = chunk_size_kb * rlib::KiB,
        .disabled = Ar::PROCESSOR_PARSE(no_ar),
        .cdc = Ar::PROCESSOR_PARSE(cdc_algo, true),
        .strict = ar_strict,
    };

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

void manifest_rads(
    std::string output,
    std::string input_manifest,
    std::string input_bundle = "",
    std::string input_release = "",
    bool append = false
) {
    RmanRads app;
    app.cli.outmanifest = output;
    app.cli.inmanifest = input_manifest;
    app.cli.inbundle = input_bundle;
    app.cli.inrelease = input_release;
    app.cli.append = append;



    if (app.cli.inrelease.empty()) {
        std::swap(app.cli.inbundle, app.cli.inrelease);
    }

    try {
        app.run();
    } catch (const std::exception& e) {
        std::string full_error = e.what();
        for (auto const& error : rlib::error_stack()) {
            full_error += "\n" + error;
        }
        rlib::error_stack().clear();
        throw std::runtime_error(full_error);
    }
}

class RmanMountHandle {
public:
    struct fuse* fuse_inst = nullptr;
    std::thread loop_thread;

    RmanMountHandle() = default;
    ~RmanMountHandle() { stop(); }

    void stop() {
        if (fuse_inst) {

            fuse_exit(fuse_inst);


            if (loop_thread.joinable()) {
                loop_thread.join();
            }


            fuse_unmount(fuse_inst);
            fuse_destroy(fuse_inst);
            fuse_inst = nullptr;
        }
    }
};


std::unique_ptr<RmanMountHandle> manifest_mount(
    std::string output,
    std::vector<std::string> manifests,
    bool fuse_debug = false,
    bool with_prefix = false,
    std::optional<std::string> filter_lang = std::nullopt,
    std::optional<std::string> filter_path = std::nullopt,
    std::string cache_path = "",
    bool cache_readonly = false,
    bool cache_newonly = false,
    uint32_t cache_buffer_mib = 32,
    uint32_t cache_limit_gib = 4,
    std::string cdn_url = "http://lol.secure.dyn.riotcdn.net/channels/public",
    size_t cdn_lowspeed_time = 0,
    size_t cdn_lowspeed_kbps = 64,
    bool cdn_verbose = false,
    long cdn_buffer_kb = 512,
    std::string cdn_proxy = "",
    std::string cdn_useragent = "",
    std::string cdn_cookiefile = "",
    std::string cdn_cookielist = ""
) {

    py::scoped_ostream_redirect stream;
    py::scoped_estream_redirect estream;


    std::vector<std::string> proxy_args = { "rman_mount" };

    if (fuse_debug) proxy_args.push_back("--fuse-debug");
    if (with_prefix) proxy_args.push_back("--with-prefix");

    proxy_args.push_back(output);
    for (const auto& m : manifests) proxy_args.push_back(m);

    std::vector<char*> c_args;
    for (auto& s : proxy_args) c_args.push_back(const_cast<char*>(s.c_str()));


    main_.parse_args((int)c_args.size(), c_args.data());


    main_.cli.output = output;
    main_.cli.manifests = manifests;
    main_.cli.with_prefix = with_prefix;
    main_.cli.match.langs = make_regex(filter_lang);
    main_.cli.match.path = make_regex(filter_path);

    main_.cli.cache = {
        .path = cache_path,
        .readonly = cache_readonly,
        .newonly = cache_newonly,
        .flush_size = cache_buffer_mib * rlib::MiB,
        .max_size = (std::uint64_t)cache_limit_gib * rlib::GiB,
    };

    main_.cli.cdn = {
        .url = rlib::clean_path(cdn_url),
        .verbose = cdn_verbose,
        .buffer = cdn_buffer_kb * 1024,
        .proxy = cdn_proxy,
        .useragent = cdn_useragent,
        .cookiefile = cdn_cookiefile,
        .cookielist = cdn_cookielist,
        .low_speed_limit = cdn_lowspeed_kbps * rlib::KiB,
        .low_speed_time = cdn_lowspeed_time,
    };



    main_.run();


    main_.fargs.argc -= 1;

    auto handle = std::make_unique<RmanMountHandle>();

    handle->fuse_inst = fuse_new(&main_.fargs, &impl_oper, sizeof(impl_oper), nullptr);
    if (!handle->fuse_inst) {
        throw std::runtime_error("FUSE Error: Failed to create instance.");
    }


    if (fuse_mount(handle->fuse_inst, main_.cli.output.c_str()) != 0) {
        fuse_destroy(handle->fuse_inst);
        throw std::runtime_error("WinFsp Error: Could not mount on " + main_.cli.output);
    }


    handle->loop_thread = std::thread([inst = handle->fuse_inst]() {

        fuse_loop_mt(inst, 0);
    });

    return handle;
}

PYBIND11_MODULE(rman_py, m) {

    m.doc() = "Python wrapper for rman";
    auto guard = py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>();

    auto m_bundle = m.def_submodule("bundle", "Tools for Riot .bundle files");
    auto m_manifest = m.def_submodule("manifest", "Tools for Riot .manifest files");

    py::class_<RmanMountHandle>(m_manifest, "MountHandle")
        .def("unmount", &RmanMountHandle::stop);


    m_manifest.def("mount", &manifest_mount,
        py::arg("output"),
        py::arg("manifests"),
        py::arg("fuse_debug") = false,
        py::arg("with_prefix") = false,
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::arg("cache_path") = "",
        py::arg("cache_readonly") = false,
        py::arg("cache_newonly") = false,
        py::arg("cache_buffer_mib") = 32,
        py::arg("cache_limit_gib") = 4,
        py::arg("cdn_url") = "http://lol.secure.dyn.riotcdn.net/channels/public",
        py::arg("cdn_lowspeed_time") = 0,
        py::arg("cdn_lowspeed_kbps") = 64,
        py::arg("cdn_verbose") = false,
        py::arg("cdn_buffer_kb") = 512,
        py::arg("cdn_proxy") = "",
        py::arg("cdn_useragent") = "",
        py::arg("cdn_cookiefile") = "",
        py::arg("cdn_cookielist") = "",
        "Mounts Riot manifests as a virtual drive with full configuration options."
    );



    m_manifest.def("download", &download,
        py::arg("manifest"),
        py::arg("output") = ".",
        py::arg("update") = "",
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::arg("no_verify") = false,
        py::arg("no_write") = false,
        py::arg("no_progress") = false,
        py::arg("cache_path") = "",
        py::arg("cache_readonly") = false,
        py::arg("cache_newonly") = false,
        py::arg("cache_buffer_mib") = 32,
        py::arg("cache_limit_gib") = 4,
        py::arg("cdn_url") = "http://lol.secure.dyn.riotcdn.net/channels/public",
        py::arg("cdn_lowspeed_time") = 0,
        py::arg("cdn_lowspeed_kbps") = 64,
        py::arg("cdn_retry") = 3,
        py::arg("cdn_workers") = 32,
        py::arg("cdn_interval_ms") = 100,
        py::arg("cdn_verbose") = false,
        py::arg("cdn_buffer_kb") = 512,
        py::arg("cdn_proxy") = "",
        py::arg("cdn_useragent") = "",
        py::arg("cdn_cookiefile") = "",
        py::arg("cdn_cookielist") = "",
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Downloads or repairs files from a Riot manifest."
    );

    m_bundle.def("check", &bundle_check,
        py::arg("inputs"),
        py::arg("no_hash") = false,
        py::arg("no_extract") = false,
        py::arg("no_progress") = false,
        py::arg("parallel") = 0,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Checks one or more bundles for errors."
    );

    m_bundle.def("extract", &bundle_extract,
        py::arg("output"),
        py::arg("inputs"),
        py::arg("with_offset") = false,
        py::arg("force") = false,
        py::arg("no_hash") = false,
        py::arg("no_progress") = false,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Extracts chunks from one or more bundles into a directory."
    );

    m_bundle.def("list", &bundle_list,
        py::arg("inputs"),
        py::arg("format") = "{bundleId},{chunkId},{compressedSize},{uncompressedSize}",
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Lists metadata for chunks inside bundles in a customizable format."
    );

    m_bundle.def("merge", &bundle_merge,
        py::arg("output"),
        py::arg("inputs"),
        py::arg("level_recompress") = 0,
        py::arg("no_extract") = false,
        py::arg("no_progress") = false,
        py::arg("newonly") = false,
        py::arg("buffer_mib") = 32,
        py::arg("limit_gib") = 4096,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Merges one or more bundles into a single output bundle with optional recompression."
    );

    m_bundle.def("usage", &bundle_usage,
        py::arg("inputs"),
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Collects and prints size usage and deduplication statistics on one or more bundles."
    );


    m_manifest.def("bundle_list", &manifest_bundle_list,
        py::arg("inputs"),
        py::arg("format") = "/{bundleId}.bundle",
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Lists the bundle IDs/names required by one or more manifests."
    );

    m_manifest.def("check", &manifest_check,
        py::arg("manifest"),
        py::arg("bundle"),
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Cross-references a manifest against a bundle to ensure all required chunks are present."
    );


    m_manifest.def("diff", &manifest_diff,
        py::arg("output"),
        py::arg("from_manifest"),
        py::arg("into_manifest"),
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Compares two manifests and creates a new one containing only the differences (added/changed files)."
    );

    m_manifest.def("list", &manifest_list,
        py::arg("manifest"),
        py::arg("format") = "{path},{size},{fileId},{langs}",
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Lists files inside a manifest with customizable formatting and regex filtering."
    );

    m_manifest.def("make", &manifest_make,
        py::arg("output_manifest"),
        py::arg("output_bundle"),
        py::arg("root_folder"),
        py::arg("inputs") = std::vector<std::string>{},
        py::arg("append") = false,
        py::arg("no_progress") = false,
        py::arg("strip_chunks") = false,
        py::arg("cdc_algo") = "fixed",
        py::arg("no_ar") = "",
        py::arg("ar_strict") = false,
        py::arg("ar_min_kb") = 4,
        py::arg("chunk_size_kb") = 1024,
        py::arg("level") = 6,
        py::arg("level_high_entropy") = 0,
        py::arg("newonly") = false,
        py::arg("buffer_mib") = 32,
        py::arg("limit_gib") = 4096,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Create a Riot manifest and bundle from a directory using smart chunking algorithms."
    );

    m_manifest.def("merge", &manifest_merge,
        py::arg("output"),
        py::arg("manifests"),
        py::arg("cache_path") = "",
        py::arg("cache_newonly") = false,
        py::arg("cache_buffer_mib") = 32,
        py::arg("cache_limit_gib") = 4096,
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::arg("strip_chunks") = false,
        py::arg("with_prefix") = false,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Merges multiple manifests into one with optional path prefixing and chunk stripping."
    );

    m_manifest.def("remake", &manifest_remake,
        py::arg("out_bundle"),
        py::arg("out_manifest"),
        py::arg("in_bundle"),
        py::arg("in_manifests"),
        py::arg("resume_file") = "",
        py::arg("resume_buffer_kb") = 64,
        py::arg("filter_lang") = py::none(),
        py::arg("filter_path") = py::none(),
        py::arg("append") = false,
        py::arg("no_progress") = false,
        py::arg("strip_chunks") = false,
        py::arg("with_prefix") = false,
        py::arg("cdc_algo") = "fixed",
        py::arg("no_ar") = "",
        py::arg("ar_strict") = false,
        py::arg("ar_min_kb") = 4,
        py::arg("chunk_size_kb") = 1024,
        py::arg("level") = 6,
        py::arg("level_high_entropy") = 0,
        py::arg("newonly") = false,
        py::arg("buffer_mib") = 32,
        py::arg("limit_gib") = 4096,
        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Remakes manifests by re-chunking data from existing bundles. Supports pausing/resuming via a resume file."
    );

    m_manifest.def("rads", &manifest_rads,
        py::arg("output"),
        py::arg("input_manifest"),
        py::arg("input_bundle") = "",
        py::arg("input_release") = "",
        py::arg("append") = false,

        py::call_guard<py::scoped_ostream_redirect, py::scoped_estream_redirect>(),
        "Converts legacy RADS project/solution data into a modern manifest format."
    );


}


