import time
import os
if os.name == 'nt':
    os.add_dll_directory(r"C:\Program Files (x86)\WinFsp\bin")
import rman_py


rman_py.bundle.check(inputs=["path/to/bundles"])
rman_py.bundle.extract(output="./out", inputs=["file.bundle"])
rman_py.bundle.list(inputs=["file.bundle"])
rman_py.bundle.merge(output="out.bundle", inputs=["in1.bundle", "in2.bundle"])
rman_py.bundle.usage(inputs=["./bundles"])


rman_py.manifest.list_bundles(inputs=["game.manifest"])
rman_py.manifest.check(manifest="game.manifest", bundle="global.bundle")
rman_py.manifest.diff(output="patch.manifest", from_manifest="v1.manifest", into_manifest="v2.manifest")
rman_py.manifest.download(manifest="game.manifest")
rman_py.manifest.list(manifest="game.manifest")
rman_py.manifest.make(output_manifest="new.manifest", output_bundle="data.bundle", root_folder="./src")
rman_py.manifest.merge(output="merged.manifest", manifests=["1.manifest", "2.manifest"])
rman_py.manifest.rads(output="out.manifest", input_manifest="in.manifest")
rman_py.manifest.remake(out_bundle="new.bundle", out_manifest="new.manifest", in_bundle="old.bundle", in_manifests=["old.manifest"])

handle = None
try:
    handle = rman_py.manifest.mount(
        output=os.path.abspath("./rman-mounted"),
        manifests=[os.path.abspath("./Manifests/RADS.json.zstd")],
        cache_path=os.path.abspath("./Bundles/RADS.bundle"),
        cache_readonly=True
    )
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("\n[Ctrl+C] Detected. Unmounting...")
except Exception as e:
    print(f"\nCRITICAL ERROR: {e}")
finally:
    if handle:
        handle.unmount()
        print("Cleanup complete.")