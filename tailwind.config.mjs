/** @type {import('tailwindcss').Config} */

export default {
    content: ["./gui/**/*.{html,js,jsx,ts,tsx}"],
    theme: {
        fontFamily: {
            sans: ["system-ui", "ui-sans-serif", "sans-serif", "emoji"],
            serif: ["ui-serif", "serif", "emoji"],
            mono: ["ui-monospace", "monospace", "emoji"],
        },
    },
    darkMode: "selector",
};
