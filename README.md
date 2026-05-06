# rman_py
Python bindings for the Riot Manifest and Bundle toolkit.

## Installation
```sh
pip install .
```

## Module: `rman_py.bundle`

### `bundle.check`
**Python Usage:**
```python
rman_py.bundle.check(inputs: collections.abc.Sequence[str], no_hash: bool = False, no_extract: bool = False, no_progress: bool = False, parallel: typing.SupportsInt | typing.SupportsIndex = 0) -> None
```
**Description & CLI Arguments:**
```text
Usage: rbun-chk.exe [-h] [--no-extract] [--no-hash] [--no-progress] [--parallel VAR] input

Checks one or more bundles for errors.

Positional arguments:
  input        	Bundle file(s) or folder(s) to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  --no-extract 	Do not even attempt to extract chunk. 
  --no-hash    	Do not verify hash. 
  --no-progress	Do not print progress to cerr. 
  --parallel   	Number of threads to use. [default: 0]
```

---

### `bundle.extract`
**Python Usage:**
```python
rman_py.bundle.extract(output: str, inputs: collections.abc.Sequence[str], with_offset: bool = False, force: bool = False, no_hash: bool = False, no_progress: bool = False) -> None
```
**Description & CLI Arguments:**
```text
Usage: rbun-ex.exe [-h] [--with-offset] [--force] [--no-hash] [--no-progress] output input

Extracts one or more bundles.

Positional arguments:
  output       	Directory to write chunks into. [required]
  input        	Bundle file(s) or folder(s) to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  --with-offset	Put hex offset in name. 
  -f, --force  	Force overwrite existing files. 
  --no-hash    	Do not verify hash. 
  --no-progress	Do not print progress to cerr.
```

---

### `bundle.list`
**Python Usage:**
```python
rman_py.bundle.list(inputs: collections.abc.Sequence[str], format: str = '{bundleId},{chunkId},{compressedSize},{uncompressedSize}') -> None
```
**Description & CLI Arguments:**
```text
Usage: rbun-ls.exe [-h] [--format VAR] input

Lists contents of one or more bundles.

Positional arguments:
  input        	Bundle file(s) or folder(s) to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  --format     	Format output. [default: "{bundleId},{chunkId},{compressedSize},{uncompressedSize}"]
```

---

### `bundle.merge`
**Python Usage:**
```python
rman_py.bundle.merge(output: str, inputs: collections.abc.Sequence[str], level_recompress: typing.SupportsInt | typing.SupportsIndex = 0, no_extract: bool = False, no_progress: bool = False, newonly: bool = False, buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, limit_gib: typing.SupportsInt | typing.SupportsIndex = 4096) -> None
```
**Description & CLI Arguments:**
```text
Usage: rbun-merge.exe [-h] [--level-recompress VAR] [--no-extract] [--no-progress] [--newonly] [--buffer VAR] [--limit VAR] output input

Adds one or more bundles into first first bundle.

Positional arguments:
  output            	Bundle file to write into. [required]
  input             	Bundle file(s) or folder to write from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help        	shows help message and exits 
  -v, --version     	prints version information and exits 
  --level-recompress	Re-compression level for zstd(0 to disable recompression). [default: 0]
  --no-extract      	Do not extract and verify chunk hash. 
  --no-progress     	Do not print progress to cerr. 
  --newonly         	Force create new part regardless of size. 
  --buffer          	Size for buffer before flush to disk in megabytes [1, 4096] [default: 32]
  --limit           	Size for bundle limit in gigabytes [0, 4096] [default: 4096]
```

---

### `bundle.usage`
**Python Usage:**
```python
rman_py.bundle.usage(inputs: collections.abc.Sequence[str]) -> None
```
**Description & CLI Arguments:**
```text
Usage: rbun-usage.exe [-h] input

Collects size usage statistics on one or more bundle.

Positional arguments:
  input        	Bundle file(s) or folder(s) to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits
```

---

## Module: `rman_py.manifest`

### `manifest.check`
**Python Usage:**
```python
rman_py.manifest.check(manifest: str, bundle: str) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-chk.exe [-h] inmanifest inbundle

Splits JRMAN .

Positional arguments:
  inmanifest   	Manifest to read from. [required]
  inbundle     	Source bundle to read from. [required]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits
```

---

### `manifest.diff`
**Python Usage:**
```python
rman_py.manifest.diff(output: str, from_manifest: str, into_manifest: str, filter_lang: str | None = None, filter_path: str | None = None) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-diff.exe [-h] [--filter-lang VAR] [--filter-path VAR] outmanifset frommanifest intomanifest

Diff files in manifest.

Positional arguments:
  outmanifset      	Manifest file to write into. [required]
  frommanifest     	Manifest file to patch from. [required]
  intomanifest     	Manifest file to patch into. [required]

Optional arguments:
  -h, --help       	shows help message and exits 
  -v, --version    	prints version information and exits 
  -l, --filter-lang	Filter: language(none for international files). [default: <not representable>]
  -p, --filter-path	Filter: path with regex match. [default: <not representable>]
```

---

### `manifest.download`
**Python Usage:**
```python
rman_py.manifest.download(manifest: str, output: str = '.', update: str = '', filter_lang: str | None = None, filter_path: str | None = None, no_verify: bool = False, no_write: bool = False, no_progress: bool = False, cache_path: str = '', cache_readonly: bool = False, cache_newonly: bool = False, cache_buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, cache_limit_gib: typing.SupportsInt | typing.SupportsIndex = 4, cdn_url: str = 'http://lol.secure.dyn.riotcdn.net/channels/public', cdn_lowspeed_time: typing.SupportsInt | typing.SupportsIndex = 0, cdn_lowspeed_kbps: typing.SupportsInt | typing.SupportsIndex = 64, cdn_retry: typing.SupportsInt | typing.SupportsIndex = 3, cdn_workers: typing.SupportsInt | typing.SupportsIndex = 32, cdn_interval_ms: typing.SupportsInt | typing.SupportsIndex = 100, cdn_verbose: bool = False, cdn_buffer_kb: typing.SupportsInt | typing.SupportsIndex = 512, cdn_proxy: str = '', cdn_useragent: str = '', cdn_cookiefile: str = '', cdn_cookielist: str = '') -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-dl.exe [-h] [--filter-lang VAR] [--filter-path VAR] [--update VAR] [--no-verify] [--no-write] [--no-progress] [--cache VAR] [--cache-readonly] [--cache-newonly] [--cache-buffer VAR] [--cache-limit VAR] [--cdn VAR] [--cdn-lowspeed-time VAR] [--cdn-lowspeed-limit VAR] [--cdn-retry VAR] [--cdn-workers VAR] [--cdn-interval VAR] [--cdn-verbose] [--cdn-buffer VAR] [--cdn-proxy VAR] [--cdn-useragent VAR] [--cdn-cookiefile VAR] [--cdn-cookielist VAR] manifest output

Downloads or repairs files in manifest.

Positional arguments:
  manifest            	Manifest file to read from. [required]
  output              	Output directory to store and verify files from. [default: "."]

Optional arguments:
  -h, --help          	shows help message and exits 
  -v, --version       	prints version information and exits 
  -l, --filter-lang   	Filter by language(none for international files) with regex match. [default: <not representable>]
  -p, --filter-path   	Filter by path with regex match. [default: <not representable>]
  -u, --update        	Filter: update from old manifest. [default: ""]
  --no-verify         	Force force full without verify. 
  --no-write          	Do not write to file. 
  --no-progress       	Do not print progress. 
  --cache             	Cache file path. [default: ""]
  --cache-readonly    	Do not write to cache. 
  --cache-newonly     	Force create new part regardless of size. 
  --cache-buffer      	Size for cache buffer in megabytes [1, 4096] [default: 32]
  --cache-limit       	Size for cache bundle limit in gigabytes [0, 4096] [default: 4]
  --cdn               	Source url to download files from. [default: "http://lol.secure.dyn.riotcdn.net/channels/public"]
  --cdn-lowspeed-time 	Curl seconds that the transfer speed should be below. [default: 0]
  --cdn-lowspeed-limit	Curl average transfer speed in killobytes per second that the transfer should be above. [default: 64]
  --cdn-retry         	Number of retries to download from url. [default: 3]
  --cdn-workers       	Number of connections per downloaded file. [default: 32]
  --cdn-interval      	Curl poll interval in miliseconds. [default: 100]
  --cdn-verbose       	Curl: verbose logging. 
  --cdn-buffer        	Curl buffer size in killobytes [1, 512]. [default: 512]
  --cdn-proxy         	Curl: proxy. [default: ""]
  --cdn-useragent     	Curl: user agent string. [default: ""]
  --cdn-cookiefile    	Curl cookie file or '-' to disable cookie engine. [default: ""]
  --cdn-cookielist    	Curl: cookie list string. [default: ""]
```

---

### `manifest.list`
**Python Usage:**
```python
rman_py.manifest.list(manifest: str, format: str = '{path},{size},{fileId},{langs}', filter_lang: str | None = None, filter_path: str | None = None) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-ls.exe [-h] [--format VAR] [--filter-lang VAR] [--filter-path VAR] manifest

Lists files in manifest.

Positional arguments:
  manifest         	Manifest file to read from. [required]

Optional arguments:
  -h, --help       	shows help message and exits 
  -v, --version    	prints version information and exits 
  --format         	Format output. [default: "{path},{size},{fileId},{langs}"]
  -l, --filter-lang	Filter: language(none for international files). [default: <not representable>]
  -p, --filter-path	Filter: path with regex match. [default: <not representable>]
```

---

### `manifest.make`
**Python Usage:**
```python
rman_py.manifest.make(output_manifest: str, output_bundle: str, root_folder: str, inputs: collections.abc.Sequence[str] = [], append: bool = False, no_progress: bool = False, strip_chunks: bool = False, cdc_algo: str = 'fixed', no_ar: str = '', ar_strict: bool = False, ar_min_kb: typing.SupportsInt | typing.SupportsIndex = 4, chunk_size_kb: typing.SupportsInt | typing.SupportsIndex = 1024, level: typing.SupportsInt | typing.SupportsIndex = 6, level_high_entropy: typing.SupportsInt | typing.SupportsIndex = 0, newonly: bool = False, buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, limit_gib: typing.SupportsInt | typing.SupportsIndex = 4096) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-make.exe [-h] [--append] [--no-progress] [--strip-chunks] [--cdc VAR] [--no-ar VAR] [--ar-strict] [--ar-min VAR] [--chunk-size VAR] [--level VAR] [--level-high-entropy VAR] [--newonly] [--buffer VAR] [--limit VAR] outmanifest outbundle rootfolder input

Lists bundle names used in manifest.

Positional arguments:
  outmanifest         	Manifest to write into. [required]
  outbundle           	Bundle file to write into. [required]
  rootfolder          	Root folder to rebase from. [required]
  input               	Files or folders for manifest. [nargs: 0 or more] [default: {}]

Optional arguments:
  -h, --help          	shows help message and exits 
  -v, --version       	prints version information and exits 
  --append            	Append manifest instead of overwriting. 
  --no-progress       	Do not print progress. 
  --strip-chunks      	
  --cdc               	Dumb chunking fallback algorithm fixed, bup [default: "fixed"]
  --no-ar             	Regex of disable smart chunkers, can be any of: fsb, fsb5, load, mac_exe, mac_fat, pe, wad, wpk, zip [default: ""]
  --ar-strict         	Do not fallback to dumb chunking on ar errors. 
  --ar-min            	Smart chunking minimum size in killobytes [1, 4096]. [default: 4]
  --chunk-size        	Chunk max size in killobytes [1, 8096]. [default: 1024]
  --level             	Compression level for zstd. [default: 6]
  --level-high-entropy	Set compression level for high entropy chunks(0 for no special handling). [default: 0]
  --newonly           	Force create new part regardless of size. 
  --buffer            	Size for buffer before flush to disk in megabytes [1, 4096] [default: 32]
  --limit             	Size for bundle limit in gigabytes [0, 4096] [default: 4096]
```

---

### `manifest.merge`
**Python Usage:**
```python
rman_py.manifest.merge(output: str, manifests: collections.abc.Sequence[str], cache_path: str = '', cache_newonly: bool = False, cache_buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, cache_limit_gib: typing.SupportsInt | typing.SupportsIndex = 4096, filter_lang: str | None = None, filter_path: str | None = None, strip_chunks: bool = False, with_prefix: bool = False) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-merge.exe [-h] [--no-progress] [--strip-chunks] [--with-prefix] [--cache VAR] [--cache-newonly] [--cache-buffer VAR] [--cache-limit VAR] [--filter-lang VAR] [--filter-path VAR] outmanifest manifests

Merges multiple manifests into one

Positional arguments:
  outmanifest      	Manifest to write into. [required]
  manifests        	Manifest files to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help       	shows help message and exits 
  -v, --version    	prints version information and exits 
  --no-progress    	Do not print progress. 
  --strip-chunks   	
  --with-prefix    	Prefix file paths with manifest name 
  --cache          	Cache file path. [default: ""]
  --cache-newonly  	Force create new part regardless of size. 
  --cache-buffer   	Size for cache buffer in megabytes [1, 4096] [default: 32]
  --cache-limit    	Size for cache bundle limit in gigabytes [0, 4096] [default: 4096]
  -l, --filter-lang	Filter: language(none for international files). [default: <not representable>]
  -p, --filter-path	Filter: path with regex match. [default: <not representable>]
```

---

### `manifest.mount`
**Python Usage:**
```python
rman_py.manifest.mount(output: str, manifests: collections.abc.Sequence[str], fuse_debug: bool = False, with_prefix: bool = False, filter_lang: str | None = None, filter_path: str | None = None, cache_path: str = '', cache_readonly: bool = False, cache_newonly: bool = False, cache_buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, cache_limit_gib: typing.SupportsInt | typing.SupportsIndex = 4, cdn_url: str = 'http://lol.secure.dyn.riotcdn.net/channels/public', cdn_lowspeed_time: typing.SupportsInt | typing.SupportsIndex = 0, cdn_lowspeed_kbps: typing.SupportsInt | typing.SupportsIndex = 64, cdn_verbose: bool = False, cdn_buffer_kb: typing.SupportsInt | typing.SupportsIndex = 512, cdn_proxy: str = '', cdn_useragent: str = '', cdn_cookiefile: str = '', cdn_cookielist: str = '') -> rman_py.manifest.MountHandle
```
**Description & CLI Arguments:**
```text
Usage: rman-mount.exe [-h] [--fuse-debug] [--with-prefix] [--filter-lang VAR] [--filter-path VAR] [--cache VAR] [--cache-readonly] [--cache-newonly] [--cache-buffer VAR] [--cache-limit VAR] [--cdn VAR] [--cdn-lowspeed-time VAR] [--cdn-lowspeed-limit VAR] [--cdn-verbose] [--cdn-buffer VAR] [--cdn-proxy VAR] [--cdn-useragent VAR] [--cdn-cookiefile VAR] [--cdn-cookielist VAR] output manifests

Mounts manifests.

Positional arguments:
  output              	output directory to mount in. [required]
  manifests           	Manifest files to read from. [nargs: 0 or more] [required]

Optional arguments:
  -h, --help          	shows help message and exits 
  -v, --version       	prints version information and exits 
  --fuse-debug        	FUSE debug 
  --with-prefix       	Prefix file paths with manifest name 
  -l, --filter-lang   	Filter by language(none for international files) with regex match. [default: <not representable>]
  -p, --filter-path   	Filter by path with regex match. [default: <not representable>]
  --cache             	Cache file path. [default: ""]
  --cache-readonly    	Do not write to cache. 
  --cache-newonly     	Force create new part regardless of size. 
  --cache-buffer      	Size for cache buffer in megabytes [1, 4096] [default: 32]
  --cache-limit       	Size for cache bundle limit in gigabytes [0, 4096] [default: 4]
  --cdn               	Source url to download files from. [default: "http://lol.secure.dyn.riotcdn.net/channels/public"]
  --cdn-lowspeed-time 	Curl seconds that the transfer speed should be below. [default: 0]
  --cdn-lowspeed-limit	Curl average transfer speed in killobytes per second that the transfer should be above. [default: 64]
  --cdn-verbose       	Curl: verbose logging. 
  --cdn-buffer        	Curl buffer size in killobytes [1, 512]. [default: 512]
  --cdn-proxy         	Curl: proxy. [default: ""]
  --cdn-useragent     	Curl: user agent string. [default: ""]
  --cdn-cookiefile    	Curl cookie file or '-' to disable cookie engine. [default: ""]
  --cdn-cookielist    	Curl: cookie list string. [default: ""]
```

---

### `manifest.rads`
**Python Usage:**
```python
rman_py.manifest.rads(output: str, input_manifest: str, input_bundle: str = '', input_release: str = '', append: bool = False) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-rads.exe [-h] [--append] outmanifest inmanifest inbundle inrelease

Splits JRMAN .

Positional arguments:
  outmanifest  	Manifest to write into. [required]
  inmanifest   	Manifest to read from. [required]
  inbundle     	Source bundle to read from. [required]
  inrelease    	Project or solution path inside bundle. If bundle is empty treat it as regex instead. [default: ""]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  --append     	Append manifest instead of overwriting.
```

---

### `manifest.remake`
**Python Usage:**
```python
rman_py.manifest.remake(out_bundle: str, out_manifest: str, in_bundle: str, in_manifests: collections.abc.Sequence[str], resume_file: str = '', resume_buffer_kb: typing.SupportsInt | typing.SupportsIndex = 64, filter_lang: str | None = None, filter_path: str | None = None, append: bool = False, no_progress: bool = False, strip_chunks: bool = False, with_prefix: bool = False, cdc_algo: str = 'fixed', no_ar: str = '', ar_strict: bool = False, ar_min_kb: typing.SupportsInt | typing.SupportsIndex = 4, chunk_size_kb: typing.SupportsInt | typing.SupportsIndex = 1024, level: typing.SupportsInt | typing.SupportsIndex = 6, level_high_entropy: typing.SupportsInt | typing.SupportsIndex = 0, newonly: bool = False, buffer_mib: typing.SupportsInt | typing.SupportsIndex = 32, limit_gib: typing.SupportsInt | typing.SupportsIndex = 4096) -> None
```
**Description & CLI Arguments:**
```text
Usage: rman-remake.exe [-h] [--filter-lang VAR] [--filter-path VAR] [--resume VAR] [--resume-buffer VAR] [--append] [--no-progress] [--strip-chunks] [--with-prefix] [--no-ar VAR] [--ar-strict] [--cdc VAR] [--ar-min VAR] [--chunk-size VAR] [--level VAR] [--level-high-entropy VAR] [--newonly] [--buffer VAR] [--limit VAR] outbundle outmanifest inbundle inmanifests

Remake manifests by rechunking all file data.

Positional arguments:
  outbundle           	Bundle file to write into. [required]
  outmanifest         	Manifest to write into. [required]
  inbundle            	Input bundle to read from [required]
  inmanifests         	Input manifests. [nargs: 0 or more] [default: {}]

Optional arguments:
  -h, --help          	shows help message and exits 
  -v, --version       	prints version information and exits 
  -l, --filter-lang   	Filter: language(none for international files). [default: <not representable>]
  -p, --filter-path   	Filter: path with regex match. [default: <not representable>]
  --resume            	Resume file path used to store processed fileIds. [default: ""]
  --resume-buffer     	Size for resume buffer before flush to disk in kilobytes [1, 16384] [default: 64]
  --append            	Append manifest instead of overwriting. 
  --no-progress       	Do not print progress. 
  --strip-chunks      	
  --with-prefix       	Prefix file paths with manifest name 
  --no-ar             	Regex of disable smart chunkers, can be any of: fsb, fsb5, load, mac_exe, mac_fat, pe, wad, wpk, zip [default: ""]
  --ar-strict         	Do not fallback to dumb chunking on ar errors. 
  --cdc               	Dumb chunking fallback algorithm fixed, bup [default: "fixed"]
  --ar-min            	Smart chunking minimum size in killobytes [1, 4096]. [default: 4]
  --chunk-size        	Chunk max size in killobytes [1, 8096]. [default: 1024]
  --level             	Compression level for zstd. [default: 6]
  --level-high-entropy	Set compression level for high entropy chunks(0 for no special handling). [default: 0]
  --newonly           	Force create new part regardless of size. 
  --buffer            	Size for buffer before flush to disk in megabytes [1, 4096] [default: 32]
  --limit             	Size for bundle limit in gigabytes [0, 4096] [default: 4096]
```

---
