import App from "components/App";
import "css/tailwind.css";
import { StrictMode } from "react";
import { createRoot } from "react-dom/client";

createRoot(document.getElementById("root") as HTMLElement).render(
    <StrictMode>
        <App />
    </StrictMode>,
);
