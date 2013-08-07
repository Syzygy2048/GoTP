#include "UIView.h"
#include "..\UIViewListener.h"
#include "..\InputHandlerSFML.h"
#include "..\AssetManager.h"

UIView::UIView(sf::Vector2i* newSize, std::string newTexture)
{
	drawAsPanel = true;
	focusable = true;
	hoverable = false;
	beingHovered= false;

	setSize(newSize);
	setTexture(newTexture);
}

void UIView::setDrawAsPanel(bool newDrawAsPanel)
{
	drawAsPanel = newDrawAsPanel;

	adjustBackGround();
}

void UIView::activated()
{
	if(listener)
	{
		listener->viewClicked(this);
	}
}

void UIView::setUIViewListener(UIViewListener* newListener)
{
	listener = newListener;
}

void UIView::onRemoveTexture()
{
	adjustBackGround();
}

void UIView::setSize(sf::Vector2i* newSize)
{
	size = newSize;

	adjustBackGround();
}

void UIView::setHoveredState(bool hoveredState)
{
	beingHovered = hoveredState;

	if (listener)
	{
		listener->viewHovered(this, beingHovered);
	}
}

void UIView::onDraw(float deltaTime, sf::RenderWindow* target, sf::Transform parentTranform)
{
	SpriteNode::onDraw(deltaTime,target, parentTranform);

	sf::FloatRect rect = sf::FloatRect(float(-size->x)/2,float(-size->y)/2,float(size->x),float(size->y));

	sf::Transform inverse = parentTranform.getInverse();

	sf::Vector2i mousePos = *InputHandlerSFML::getInstance()->getMousePosition();

	sf::Vector2f transformedPoint = inverse.transformPoint(float(mousePos.x),float(mousePos.y));

	if(rect.contains(transformedPoint))
	{
		AssetManager::getInstance()->setDrawnClickable(this);
	}
}

void UIView::onSetTexture()
{
	adjustBackGround();
}

void UIView::adjustBackGround()
{
	if (!drawAsPanel)
	{
		sprite->setScale(float(size->x)/texture->getSize().x,float(size->y)/texture->getSize().y);

		sprite->setTexture(*texture);

		return;
	}
	else
	{
		sprite->setScale(1,1);
	}

	sf::RenderTexture destinationTexture = sf::RenderTexture();

	destinationTexture.create(size->x,size->y);

	if(texture)
	{
		int tileSize = texture->getSize().x/3;

		if (tileSize*2 > size->x || tileSize*2 > size->y)
		{
			std::cout<< "Size of view too small for texture selected.\n";
		}
		else
		{
			destinationTexture.clear(sf::Color::Transparent);

			sf::Sprite tempSprite = sf::Sprite();

			tempSprite.setTexture(*texture);

			int verticalFillSpace = size->y;
			int verticalDrawingPoint = 0;

			while (verticalFillSpace > 0)
			{
				int referenceVerticalPoint = 0;

				//are we not filling the first line?
				if(verticalDrawingPoint)
				{
					//are we filling the bottom?
					if (verticalFillSpace <= tileSize)
					{
						referenceVerticalPoint = tileSize*2;
					}
					else
					{
						referenceVerticalPoint = tileSize;
					}
				}

				//we draw the left chunk
				tempSprite.setPosition(0.f,float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(0,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture.draw(tempSprite);

				//the right chunk
				tempSprite.setPosition(float(size->x-tileSize),float(verticalDrawingPoint));
				tempSprite.setTextureRect(sf::IntRect(tileSize*2,referenceVerticalPoint,tileSize,tileSize));
				destinationTexture.draw(tempSprite);

				int horizontalFillingSpace = size->x - (tileSize*2);
				int horizontalDrawingPoint = tileSize;

				tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,tileSize,tileSize));

				//now we fill the horizontal gap
				while (horizontalFillingSpace > 0)
				{
					//are we drawing the last one?
					if (horizontalFillingSpace<tileSize)
					{
						tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,horizontalFillingSpace,tileSize));
					}

					tempSprite.setPosition(float(horizontalDrawingPoint),float(verticalDrawingPoint));
					destinationTexture.draw(tempSprite);

					horizontalDrawingPoint +=tileSize;
					horizontalFillingSpace -= tileSize;
				}

				verticalFillSpace -= tileSize;

				if (verticalFillSpace < tileSize)
				{
					verticalDrawingPoint += verticalFillSpace;
				}
				else
				{
					verticalDrawingPoint += tileSize;
				}
			}
		}
	}
	else
	{
		destinationTexture.clear(sprite->getColor());
	}

	if(text)
	{
		destinationTexture.draw(*text);
	}

	destinationTexture.display();

	if(finalTexture)
	{
		delete finalTexture;
	}

	finalTexture = new sf::Texture(destinationTexture.getTexture());

	finalTexture->setSmooth(true);

	sprite->setTexture(*finalTexture);

	sprite->setPosition(-float(finalTexture->getSize().x)/2,-float((finalTexture->getSize().y)/2));

}

void UIView::setText(sf::Text* newText)
{
	if (text)
	{
		delete text;
	}

	text = newText;

	adjustBackGround();
}

UIView::~UIView(void)
{
	if (finalTexture)
	{
		delete finalTexture;
	}

	if (text)
	{
		delete text;
	}

	if (size)
	{
		delete size;
	}
}