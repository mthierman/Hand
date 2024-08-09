import react from "@vitejs/plugin-react-swc";
import { resolve } from "path";
import { CommonServerOptions, UserConfig, defineConfig } from "vite";

const userConfig: UserConfig = {
    plugins: [react()],
    root: "gui",
    // resolve: {
    //     alias: {
    //         components: resolve("src/components"),
    //         css: resolve("src/css"),
    //     },
    // },
};

const commonServerOptions: CommonServerOptions = {
    port: 8000,
    https: {
        pfx: resolve("../.cert/localhost.pfx"),
        passphrase: "localhost",
    },
};

// https://vitejs.dev/config/
export default defineConfig(({ command }) => {
    switch (command) {
        case "serve": {
            return {
                ...userConfig,
                server: { ...commonServerOptions },
                preview: { ...commonServerOptions },
            };
        }
        default: {
            return {
                ...userConfig,
            };
        }
    }
});
