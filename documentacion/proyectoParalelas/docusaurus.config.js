// @ts-check
// `@type` JSDoc annotations allow editor autocompletion and type checking
// (when paired with `@ts-check`).
// There are various equivalent ways to declare your Docusaurus config.
// See: https://docusaurus.io/docs/api/docusaurus-config

import { themes as prismThemes } from "prism-react-renderer";

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: "Proyecto Computacion Paralela y Distribuida",
  tagline: "Un proyecto de Screensaver con SDL, OpenMP y C",
  favicon: "img/favicon.ico",

  // Set the production url of your site here
  url: "https://your-docusaurus-site.example.com",
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: "/",

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: "Universidad del Valle de Guatemala", // Usually your GitHub org/user name.
  projectName: "Proyecto Computacion Paralela y Distribuida", // Usually your repo name.

  onBrokenLinks: "throw",
  onBrokenMarkdownLinks: "warn",

  // Even if you don't use internationalization, you can use this field to set
  // useful metadata like html lang. For example, if your site is Chinese, you
  // may want to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: "en",
    locales: ["en"],
  },

  presets: [
    [
      "classic",
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: "./sidebars.js",
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            "https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/",
        },
        blog: {
          showReadingTime: true,
          feedOptions: {
            type: ["rss", "atom"],
            xslt: true,
          },
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            "https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/",
        },
        theme: {
          customCss: "./src/css/custom.css",
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      // Replace with your project's social card
      image: "img/docusaurus-social-card.jpg",
      navbar: {
        title: "Proyecto",
        logo: {
          alt: "My Site Logo",
          src: "img/paralelasLogo.png",
        },
        items: [
          {
            type: "docSidebar",
            sidebarId: "tutorialSidebar",
            position: "left",
            label: "Tutorial",
          },
          {
            href: "https://github.com/jazurdia/screensaver_p1.git",
            label: "GitHub",
            position: "right",
          },
        ],
      },
      footer: {
        style: "dark",
        links: [
          {
            title: "Domentacion",
            items: [
              {
                label: "Introducción",
                to: "/docs/intro",
              },
            ],
          },
          {
            title: "Desarrolladores",
            items: [
              {
                label: "Angel Castellanos",
                href: "https://angelcastellanoscv.netlify.app/",
              },
              {
                label: "Alejandro Azurdia",
                href: "https://www.linkedin.com/in/alejandro-azurdia-236a61279/",
              },
              {
                label: "Diego Morales",
                href: "https://www.linkedin.com/in/diego-morales-343809204/",
              },
            ],
          },
          {
            title: "Más",
            items: [
              {
                label: "GitHub",
                href: "https://github.com/jazurdia/screensaver_p1.git",
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} Proyecto. Built with Docusaurus.`,
      },
      prism: {
        theme: prismThemes.github,
        darkTheme: prismThemes.dracula,
        additionalLanguages: ['c', 'bash'],
      },
    }),
};

export default config;
