#!/usr/bin/env node
import child_process from "child_process";
import path from 'path';
import fs from 'fs';

async function compile() {
    let compilation = child_process.spawn('cmake', ['--build', 'build', '-j10']);

    compilation.stdout.setEncoding('utf-8');
    compilation.stderr.setEncoding('utf-8');

    compilation.stdout.on('data', data => {
        console.log(data);
    });

    compilation.stderr.on('data', data => {
        console.error(data);
    });

    return new Promise((resolve, reject) => {
        compilation.on('close', resolve);
    });
}

const __dirname = path.resolve();

try {
    child_process.execSync('cmake --version');
} catch (err) {
    console.error(err, "\nplease install cmake before trying to install claw-js.");
}

try {
    child_process.execSync('ninja --version');
} catch (err) {
    console.error(err, "\nplease install ninja before trying to install claw-js.");
}

(async () => {
    try {
        child_process.execSync(`git clone --recursive --branch clblast https://github.com/tussoftwaredesign/claw-js.git ${__dirname}/node_modules/claw-src`);

        process.chdir(`${__dirname}/node_modules/claw-src`);

        child_process.execSync('mkdir build');

        child_process.execSync(`cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release`);
        await compile();

        let libclaw = 'libclaw.so';

        switch (process.platform) {
            case "darwin":
                libclaw = "libclaw.dylib";
                break;
            case "win32":
                libclaw = "libclaw.dll";
                break;
        }

        if (!fs.existsSync('../.bin')) {
            fs.mkdirSync('../.bin');
        }

        fs.renameSync(`./build/${libclaw}`, `../.bin/${libclaw}`);

        const libclawAbsolutePath = `${__dirname}/node_modules/.bin/${libclaw}`;

        fs.writeFileSync('../claw-js/.env', `LIBCLAW_PATH=${libclawAbsolutePath}`);

        process.chdir(`../..`);
        fs.rmSync('./node_modules/claw-src', {force: true, recursive: true});
    } catch (err) {
        console.error(err);
    }
})();