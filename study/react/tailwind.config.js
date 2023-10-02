/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./src/**/*.{html,js,ts,jsx,tsx}",
  ],
  theme: {
    minWidth: {
      '208': '208px',
    },
    extend: {},
  },
  plugins: [require("daisyui")],
}