export interface ButtonProps {
    text?: string;
}

export const Button = ({ text = "Button" }: ButtonProps) => {
    return <button className="rounded border-2 border-blue-400 p-2 text-blue-400">{text}</button>;
};
